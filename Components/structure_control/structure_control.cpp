//-----------------------------------------------------------------------------
//	MODULE		:	structure_control.cpp
//	PROJECT		:	em8600_probe
//	PROGRAMMER	:	Michael A. Uman
//	DATE		:	September 2005
//	LAST MOD	:	March 20, 2014
//	COPYRIGHT	:	(C) 2005-2014 Sigma Designs
//-----------------------------------------------------------------------------


/**
    NOTE:   This code does not handle embedded unions nor bitfields properly.
 */

//#define _VERBOSE_ERRORS   1       /* enable error output to stderr        */
//#define _ENABLE_PIPE      1       /* enable processing interface headers  */
//#define _EXPANDED_DEBUG   1       /* enable additional debugging msg      */
//#define _ENABLE_EXCEL     1
#define PF_BUF_SIZE	        (4096)  /* Size of line buffer                  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <string>
#include <vector>
#include <tre/tre.h>
#include <sys/stat.h>
#include "structure_control.h"
#include "dbgutils.h"

#ifdef  _ENABLE_EXCEL
#   include <xlslib.h>
using namespace xlslib_core;
#endif

extern "C" {
    #include "sc_tcalc.hpp"
    #include "sc_lexer.h"

    extern int parse_expression(const char* szExpression);
}

member_definition::member_definition(const char* member, const char* type, size_t offset)
:	member_name(member),
	member_type(type),
	member_offset(offset),
	member_flags(flag_variable),
	member_maxindex(0)
{
}

member_definition::member_definition(const char* member, const char* type, size_t index, size_t offset)
:	member_name(member),
	member_type(type),
	member_offset(offset),
	member_flags(flag_array),
	member_maxindex(index)
{
}

member_definition::member_definition(const member_definition& copy) {
	member_name 	= copy.member_name;
	member_type 	= copy.member_type;
	member_offset 	= copy.member_offset;
	member_flags 	= copy.member_flags;
	member_maxindex	= copy.member_maxindex;
}


member_definition::~member_definition() {
}

union_definition::union_definition(structure_database* db, const char* name)
: 	struct_db(db),
	struct_name(name),
	last_offset(0L)
{
	//D(debug("union_definition::union_definition(%s)\n", name));
}

union_definition::~union_definition() {
	members.clear();
}

void union_definition::add_member(const char* name, const char* type, size_t offset) {
	size_t		member_size = 0L;

	member_size	= struct_db->get_type_size(type);

	//D(debug("-- adding member %s to union %s offset = %d size = %d\n", name, struct_name.c_str(), offset, member_size));

	member_definition	member(name, type, offset);

	members.push_back(member);

	if (last_offset < member_size)
		last_offset = member_size;

	return;
}

void union_definition::add_array_member(const char* name, const char* type, int index, size_t offset) {
	size_t		member_size = 0L;

	//D(debug("union_definition::add_array_member(%s, %s, %d, %d)\n", name, type, index, offset));

	member_size	= struct_db->get_type_size(type) * index;

	//debug("-- adding member %s [array of %d %s] to union %s offset = %d size = %d\n", name, index, type,
	//  		struct_name.c_str(), offset, member_size);

	member_definition	member(name, type, index, offset);

	members.push_back(member);

	if (last_offset < member_size)
		last_offset = member_size;

	return;
}

const member_definition* union_definition::member(int index) const {
	if ((size_t)index < members.size()) {
		return &members[index];
	} else {
		return (member_definition*)0L;
	}
}

structure_definition::structure_definition(structure_database* db, const char* name)
: 	struct_db(db),
	struct_name(name),
	last_offset(0L)
{

}

structure_definition::~structure_definition() {
	members.clear();
}


void structure_definition::add_member(const char* name, const char* type, size_t offset) {
	size_t		member_size = 0L;

	if (offset == 0) {
		offset = last_offset;
	}

	member_size	= struct_db->get_type_size(type);

	//D(debug("-- adding member %s to structure %s offset = %d size = %d\n", name, struct_name.c_str(), offset, member_size));

	member_definition	member(name, type, offset);

	members.push_back(member);

	last_offset += member_size;
}

/**
 *
 */

void structure_definition::add_member_size(const char* name, const char* type, size_t size) {
    size_t      offset = last_offset;

	D2(debug("-- adding member %s to structure %s last_offset = %d offset = %d size = %d\n",
         name, struct_name.c_str(), last_offset, offset, size));

	member_definition	member(name, type, offset);

	members.push_back(member);

	last_offset += size;
}

void structure_definition::add_union_member(const char* name, const char* type, size_t offset) {
	size_t		member_size = 0L;

	//D(debug("structure_definition::add_union_member(%s, %s, %d)\n", name, type, offset));

	if (offset == 0) {
		offset = last_offset;
	}

	member_size	= struct_db->get_union_size(type);

	//D(debug("-- adding union %s to structure %s offset = %d size = %d\n", name, struct_name.c_str(), offset, member_size));

	member_definition	member(name, type, offset);

	members.push_back(member);

	last_offset += member_size;

	return;
}


void structure_definition::add_array_member(const char* name, const char* type, int index, size_t offset) {
	size_t		member_size = 0L;

	//D(debug("add_array_member(%s, %s, %d, %d)\n", name, type, index, offset));

	if (offset == 0) {
		offset = last_offset;
	}

	member_size	= struct_db->get_type_size(type) * index;

	member_definition	member(name, type, index, offset);

	members.push_back(member);

	last_offset += member_size;
}

const member_definition* structure_definition::member(const char* member) const {
	for (size_t i = 0 ; i < members.size() ; i++) {
		const member_definition*	pMemb = this->member(i);

		if (strcmp(pMemb->name().c_str(), member) == 0) {
			return pMemb;
		}
	}

	return (member_definition*)0L;
}

const member_definition* structure_definition::member(int index) const {
	if ((size_t)index < members.size()) {
		return &members[index];
	} else {
		return (member_definition*)0L;
	}
}


/**
    structure_database constructor
 */

structure_database::structure_database()
:   ifp(0),
    unnamedStructIndex(0),
    unnamedUnionIndex(0)
{
    D(debug("structure_database::structure_database()\n"));
    push_state(FLAGS_NONE, (void*)0L);
}

structure_database::~structure_database() {
    D(debug("structure_database::~structure_database()\n"));
	reset();
}

size_t structure_database::get_union_size(const char* type) {
	union_definition*	pUnion = 0L;

	for (size_t i = 0 ; i < union_vector.size() ; i++) {
		if (strcmp(union_vector[i]->name().c_str(), type) == 0) {
			pUnion = union_vector[i];
			return pUnion->size();
		}
	}

	return 0L;
}

size_t structure_database::get_type_size(const char* type) {
	size_t		result = 0L;

	if (strncmp(type, "RMuint64", 8) == 0) {
		result = 8;
	} else if (strncmp(type, "RMuint32", 8) == 0) {
		result = 4;
	} else if (strncmp(type, "RMuint16", 8) == 0) {
		result = 2;
	} else if (strncmp(type, "RMuint8", 7) == 0) {
		result = 1;
	} else if (strncmp(type, "RMbool", 6) == 0) {
		result = 1;
	} else if (strncmp(type, "dw", 2) == 0) {
	    result = 2;
	} else {
		const structure_definition*	pDef = get_structure(type);

		if (pDef != NULL) {
			result = pDef->size();
		} else {
			const union_definition* pUnion = get_union(type);

			if (pUnion != NULL) {
				result = pUnion->size();
			} else {
				result = 4;
			}
		}
	}

	return result;
}

const structure_definition* structure_database::get_structure(const char* name) {
    D(debug("structure_database::get_structure(%s)\n", name));

	for (size_t i = 0 ; i < size() ; i++) {
		const structure_definition*	pDef = (*this)[i];

		if ((strcmp(name, pDef->name().c_str())) == 0) {
			return pDef;
		}
	}

	return (structure_definition*)0L;
}

const union_definition* structure_database::get_union(const char* name) {
    D(debug("structure_database::get_union(%s)\n", name));

	for (size_t i = 0 ; i < union_vector.size() ; i++) {
		const union_definition*	pDef = union_vector[i];

		if ((strcmp(name, pDef->name().c_str())) == 0) {
			return pDef;
		}
	}

	return (union_definition*)0L;
}

/**
    Insert new structure into structure vector, in sorted order...
 */
structure_definition* structure_database::new_structure(const char* name) {
	structure_definition*	result = 0L;

    D2(debug("structure_database::new_structure(%s)\n", name));

	result = new structure_definition(this, name);
    assert( result != 0L);

    STRUCTURE_VECTOR::iterator it;

    for (it = structure_vector.begin() ; it != structure_vector.end() ; it++) {
        if ( (*it)->name() >= name )
            break;
    }

    structure_vector.insert( it, result );

	return result;
}

union_definition* structure_database::new_union(const char* name) {
	union_definition*	result = 0L;

    D2(debug("structure_database::new_union(%s)\n", name));

	result = new union_definition(this, name);

	union_vector.push_back(result);

	return result;
}

void structure_database::reset() {
    D(debug("structure_database::reset()\n"));

	for (size_t i = 0 ; i < structure_vector.size() ; i++) {
		delete structure_vector[i];
	}

	structure_vector.clear();

	for (size_t i = 0 ; i < union_vector.size() ; i++) {
		delete union_vector[i];
	}

	union_vector.clear();
}

bool structure_database::open(const char* filename) {
    D(debug("structure_database::open(%s)\n", filename));
//	reset();
	return parse_file(filename);
}

/*
 *	parse_file
 *
 *	If filename ends in .h then file is passed through 'cpp' preprocessor, if
 *	the filename ends in .hh then the file is not preprocessed.
 *
 */

bool structure_database::parse_file(const char* filename) {
	bool		result = true;
#ifdef  _ENABLE_PIPE
	char*		env = 0L;
	bool		bUsePipe = false;
	static char	szCommand[MAX_CMD];
#endif
    void*       pConstruct = 0;
	struct stat status;

//	--	Verify that the file exists...

	D(debug("structure_database::parse_file(%s)\n", filename));

	if (stat(filename, &status) == -1) {
        D(debug("ERROR: Header file %s not found!\n", filename));
#ifdef  _VERBOSE_ERRORS
		fprintf(stderr, "ERROR: Header file %s not found!\n", filename);
#endif
		return false;
	}

#ifdef  _ENABLE_PIPE
//	--	Check if file extension is .h, if so set bUsePipe to true

	{
		const char		*pExt = 0;
		char		ext[32];

		if ((pExt = rindex(filename, '.')) != 0) {
			strncpy(ext, pExt, 32);
		}

//	--	If file ends in '.h'

        D(debug("-- extension %s\n", ext));

		if (strcmp(ext, ".hh") == 0) {
			bUsePipe = false;
		} else if (strcmp(ext, ".h") == 0) {
			bUsePipe = true;
		}

	}
#endif

    /* initialize the regular expression parser */
    init_regexp_parser();

#ifdef  _ENABLE_PIPE

//	--	Open file piped through CPP (C Preprocessor)...

	if (bUsePipe == true) {
		static char		RMCFLAGS[256] = {0};

		if ((env = getenv("RMCFLAGS")) == 0) {
#ifdef  _VERBOSE_ERRORS
			fprintf(stderr, "ERROR: Environment RMCFLAGS not initialized!\n");
#endif
			return false;
		}

		//D(debug("-- piping %s through C preprocessor...\n", filename));

		strncpy(RMCFLAGS, env, 256);

		snprintf(szCommand, MAX_CMD, "cpp 2> /dev/null %s %s", RMCFLAGS, filename);
		ifp = popen(szCommand, "r");
	} else {
		ifp = fopen(filename, "r");
	}

#else   // _ENABLE_PIPE

    ifp = fopen(filename, "r");

#endif  // _ENABLE_PIPE

	if (ifp == 0) {
#ifdef  _VERBOSE_ERRORS
		fprintf(stderr, "ERROR: Unable to open CPP pipe...\n");
#endif
		return false;
	}

	{
		regmatch_t		matches[4];
		char*	lineptr = 0;
		int		flags = 0;
        int     lineNo = 0;

		lineptr = (char *)malloc(PF_BUF_SIZE);

		while (NULL != fgets(lineptr, PF_BUF_SIZE, ifp)) {
		    lineNo++;

			if (!feof(ifp) && ('\n' != lineptr[strlen(lineptr) - 1])) {
				/* error: the line was too long to fit in lineptr */

#ifdef  _VERBOSE_ERRORS
				fprintf(stderr, "ERROR: line #%d too long (more than %d characters.)\n",
						lineNo, PF_BUF_SIZE );
#endif
				result = false;
				break;
			}

//			//D(debug("line > %s", lineptr));

			if ((*lineptr == '\n') || (lineptr[0] == '#')) {
				continue;
			}

            flags = peek_state(&pConstruct);

#ifdef  _EXPANDED_DEBUG
            fprintf(stderr, "%d|%02x|%08x : %s", lineNo, flags, (unsigned int)pConstruct, lineptr);
#endif

            if (flags == FLAGS_NONE) {

//                D(debug("A\n"));

                if (regexec(&exp_startstruct, lineptr, 2, matches, 0) == 0) {
                    char*	struct_name;
                    size_t	len = matches[1].rm_eo - matches[1].rm_so;
                    structure_definition*		pStruct = 0;

                    struct_name 		= new char[len + 1];
                    struct_name[len ] 	= 0;

                    strncpy(struct_name, lineptr + matches[1].rm_so, len );
                    D(debug( "START STRUCT %s:\n", struct_name));

                    /* do not add if structure already exists */
                    if (get_structure(struct_name) == 0) {
                        pStruct = new_structure(struct_name);
                        push_state(FLAGS_IN_STRUCT, (void*)pStruct);
                    } else {
                        D(debug("Duplicate structure [%s]\n", struct_name));
                    }

                    delete [] struct_name;
                    continue;
                } else if (regexec(&exp_start_namedunion, lineptr, 2, matches, 0) == 0) {
                    char*	union_name;
                    size_t	len = matches[1].rm_eo - matches[1].rm_so;
                    union_definition*			pUnion = 0;

                    union_name 		    = new char[len + 1];
                    union_name[len ] 	= 0;

                    strncpy(union_name, lineptr + matches[1].rm_so, len );

                    D(debug("START UNION %s\n", union_name));

                    /* do not add if union already exists */
                    if (get_union(union_name) == 0) {
                        pUnion = new_union(union_name);
                        push_state(FLAGS_IN_UNION, (void*)pUnion);
                    } else {
                        D(debug("Duplicate union [%s]\n", union_name));
                    }

                    delete [] union_name;
                    continue;
                }
            }

            if (FLAG_ISSET(flags, FLAGS_IN_STRUCT) || FLAG_ISSET(flags, FLAGS_IN_UNNAMEDSTRUCT) || FLAG_ISSET(flags, FLAGS_IN_UNION) || FLAG_ISSET(flags, FLAGS_IN_UNNAMEDUNION)) {
                char	member_type[1024], member_name[1024], member_index[1024];

//                D(debug("B\n"));

                if (regexec(&exp_endstruct, lineptr, 0, NULL, 0) == 0) {
                    D(debug("-- end of structure or union!\n"));
                    pop_state();
                } else if ((FLAG_ISSET(flags, FLAGS_IN_UNNAMEDSTRUCT) || FLAG_ISSET(flags, FLAGS_IN_UNNAMEDUNION))
                        && regexec(&exp_end_unnamed_struct, lineptr, 2, matches, 0) == 0) {
                    int nextFlag;
                    structure_definition *unnamed_struct_def = 0; //, *struct_def = 0;
                    size_t    len = matches[1].rm_eo - matches[1].rm_so;

                    member_name[len] = 0;
                    strncpy(member_name, lineptr + matches[1].rm_so, len);

                    pop_state(0, (void**)&unnamed_struct_def);

                    D(debug("-- end of unnamed struct [%s] %s!\n", unnamed_struct_def->name().c_str(), member_name));
                    nextFlag = peek_state(&pConstruct);

                    assert(pConstruct != 0L);
                    if (FLAG_ISSET(nextFlag, FLAGS_IN_STRUCT) || FLAG_ISSET(nextFlag, FLAGS_IN_UNNAMEDSTRUCT)) {
                        D(debug("-- adding member %s of type %s to structure %s...\n", member_name, unnamed_struct_def->name().c_str(), ((structure_definition*)pConstruct)->name().c_str()));
                        if (FLAG_ISSET(flags, FLAGS_IN_STRUCT) || FLAG_ISSET(flags, FLAGS_IN_UNNAMEDSTRUCT)) {
                            ((structure_definition*)pConstruct)->add_member(member_name, unnamed_struct_def->name().c_str());
                        } else if (FLAG_ISSET(flags, FLAGS_IN_UNION) || FLAG_ISSET(flags, FLAGS_IN_UNNAMEDUNION)) {
                            ((structure_definition*)pConstruct)->add_union_member(member_name, unnamed_struct_def->name().c_str());
                        }
                    } else if (FLAG_ISSET(nextFlag, FLAGS_IN_UNION) || FLAG_ISSET(nextFlag, FLAGS_IN_UNNAMEDUNION)) {
                        D(debug("-- adding member %s of type %s to union %s...\n", member_name, unnamed_struct_def->name().c_str(), ((union_definition*)pConstruct)->name().c_str()));
                        ((union_definition*)pConstruct)->add_member(member_name, unnamed_struct_def->name().c_str());
                    }
                } else {

    //	--	Check if member is a structure...

                    if (regexec(&exp_array_membstruct, lineptr, 4, matches, 0) == 0) {
                        unsigned int member_index_size = 0;
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;

#if 1
                        /* This code removes any spaces embedded in type */
                        for (size_t i = 0, j = 0 ; i < len ; i++) {
                            char ch = *(lineptr + matches[1].rm_so + i);
                            if (ch != ' ') {
                                member_type[j++] = ch;
                                member_type[j] = 0;
                            }
                        }
#else
                        member_type[len] = 0;
                        strncpy(member_type, lineptr + matches[1].rm_so, len);
#endif

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

                        len = matches[3].rm_eo - matches[3].rm_so;
                        member_index[len] = 0;
                        strncpy(member_index, lineptr + matches[3].rm_so, len);

                        member_index_size = calculate_array_size(member_index);

                        D(debug("-- STRUCTURE ARRAY %s TYPE %s SIZE %d!\n", member_name, member_type, member_index_size));

                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
//                            pStruct->add_array_member(member_name, member_type, atoi(member_index));
                            ((structure_definition*)pConstruct)->add_array_member(member_name, member_type, member_index_size);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_array_member(member_name, member_type, member_index_size);
                        }

                    } else if (regexec(&exp_membstruct, lineptr, 3, matches, 0) == 0) {
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;

                        /* This code removes any spaces embedded in type */
                        for (size_t i = 0, j = 0 ; i < len ; i++) {
                            char ch = *(lineptr + matches[1].rm_so + i);
                            if (ch != ' ') {
                                member_type[j++] = ch;
                                member_type[j] = 0;
                            }
                        }

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

                        D(debug("STRUCTURE MEMBER type %s name %s!\n", member_type, member_name));

    //	--	Add this member to the current structure...


                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
                            ((structure_definition*)pConstruct)->add_member(member_name, member_type);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_member(member_name, member_type);
                        }
                    } else if (regexec(&exp_memb_unnamed_struct, lineptr, 3, matches, 0) == 0) {
                        STRING structName;
                        structure_definition*		pStruct = 0;

                        get_next_unnamed_struct(structName);
                        D(debug("Encountered unnamed struct [%s]!\n", structName.c_str()));
                        pStruct = new_structure( structName.c_str() );
                        push_state(FLAGS_IN_UNNAMEDSTRUCT, pStruct);
//                        get_unnamed_struct();
                    } else if (regexec(&exp_memb_unnamed_union, lineptr, 3, matches, 0) == 0) {
                        STRING unionName;
                        union_definition* pUnion;

                        get_next_unnamed_union(unionName);

                        D(debug("Encountered unnamed union %s!\n", unionName.c_str()));
                        pUnion = new_union( unionName.c_str() );

                        push_state(FLAGS_IN_UNNAMEDUNION, pUnion);
                    } else if (regexec(&exp_membenum, lineptr, 3, matches, 0) == 0) {
    //					char	member_type[128], member_name[128];
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;

                        member_type[len] = 0;
                        strncpy(member_type, lineptr + matches[1].rm_so, len);

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

                        D(debug("ENUM MEMBER type %s name %s!\n", member_type, member_name));

    //	--	Add this member to the current structure...


                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
                            ((structure_definition*)pConstruct)->add_member(member_name, member_type);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_member(member_name, member_type);
                        }

                    }  else if (regexec(&exp_array_member, lineptr, 4, matches, 0) == 0) {
                        unsigned int member_index_size = 0;
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;
                        member_type[len] = 0;
                        strncpy(member_type, lineptr + matches[1].rm_so, len);

//                        printf("\nline %d : %s", lineNo, lineptr);
//                        printf("type %s\n", member_type);

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

//                        printf("name %s\n", member_name);

                        len = matches[3].rm_eo - matches[3].rm_so;
                        member_index[len] = 0;
                        strncpy(member_index, lineptr + matches[3].rm_so, len);

                        //printf("index %s\n", member_index);

                        member_index_size = calculate_array_size(member_index);

                        //printf("size %d\n", member_index_size);

                        D(debug("ARRAY MEMBER %s TYPE %s SIZE [%s] = %d!\n", member_name, member_type, member_index, member_index_size));

                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
                            ((structure_definition*)pConstruct)->add_array_member(member_name, member_type, member_index_size);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_array_member(member_name, member_type, member_index_size);
                        }

                    } else if (regexec(&exp_member, lineptr, 3, matches, 0) == 0) {
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;

                        member_type[len] = 0;
                        strncpy(member_type, lineptr + matches[1].rm_so, len);

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

                        D(debug("MEMBER %s TYPE %s\n", member_name, member_type));

                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
                            ((structure_definition*)pConstruct)->add_member(member_name, member_type);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_member(member_name, member_type);
                        }
                    } else if (regexec(&exp_memb_union, lineptr, 3, matches, 0) == 0) {
                        size_t	len = matches[1].rm_eo - matches[1].rm_so;
                        D(debug("FOUND UNION MEMBER!\n"));

                        member_type[len] = 0;
                        strncpy(member_type, lineptr + matches[1].rm_so, len);

                        len = matches[2].rm_eo - matches[2].rm_so;
                        member_name[len] = 0;
                        strncpy(member_name, lineptr + matches[2].rm_so, len);

                        D(debug("MEMBER %s TYPE %s\n", member_name, member_type));
                        if ((flags & FLAGS_IN_STRUCT) || (flags & FLAGS_IN_UNNAMEDSTRUCT)) {
                            assert(pConstruct != 0L);
                            ((structure_definition*)pConstruct)->add_member(member_name, member_type);
                        } else if ((flags & FLAGS_IN_UNION) || (flags & FLAGS_IN_UNNAMEDUNION)) {
                            assert(pConstruct != 0L);
                            ((union_definition*)pConstruct)->add_member(member_name, member_type);
                        }
                    } else {
                        D(debug("UNKNOWN %s", lineptr));
                        //printf("%s\n", lineptr);
                    }

                }
            }
		}
		free(lineptr);
		lineptr = 0;
	}

//exit_open:
#ifdef  _ENABLE_PIPE
	if (bUsePipe) {
		pclose(ifp);
	} else {
		fclose(ifp);
	}
#else   // _ENABLE_PIPE
    fclose(ifp);
#endif  // _ENABLE_PIPE

	ifp = 0L;

//	--	Free all REGEXP expressions...

    release_regexp_parser();

#ifdef	_ENABLE_DUMP
	dump( stderr );
#endif	// DUMP

	return result;
}

#ifdef  _ENABLE_HTML_OUTPUT
void structure_database::dump_html_table(const char* szFileName, const char* szHeading) {
    FILE*   pFP;

    pFP = fopen(szFileName, "w");
    fprintf(pFP, "<html>\n<head>\n");
    if (szHeading == 0L) {
        fprintf(pFP, "\t<title>Structure Analysis</title>\n");
    } else {
        fprintf(pFP, "\t<title>%s</title>\n", szHeading);
    }

    fprintf(pFP, "<style type=\"text/css\">\n");
    fprintf(pFP, "\ttable { font-family:monospace; font-size: 10pt; }\n");
    fprintf(pFP, "\tcaption { color: blue; font-family: helvetica; font-size: 12pt; font-weight: bold; }\n");
    fprintf(pFP, "\tth { font-family: helvetica; font-weight: bold; color: red; }\n");
    fprintf(pFP, "</style>\n");
    fprintf(pFP, "</head>\n<body>\n");
    fprintf(pFP, "<center>\n");
    fprintf(pFP, "<h1>Structure Analysis</h1>\n");
    if (szHeading != 0) {
        fprintf(pFP,"<h2>%s</h2>\n", szHeading);
    }
    fprintf(pFP, "</center>\n");
    fprintf(pFP, "<h3>Structures</h3>\n");
	fprintf(pFP, "<ul>\n");
	for (size_t i = 0 ; i < size() ; i++) {
		const structure_definition*	pDef = (*this)[i];
        fprintf(pFP, "\t<li><a href=\"#%s\">%s</a></li>\n", pDef->name().c_str(),pDef->name().c_str());
	}
    fprintf(pFP, "</ul>\n");
    fprintf(pFP, "<h3>Unions</h3>\n");
    fprintf(pFP, "<ul>\n");
    for (size_t i = 0 ; i < union_vector.size() ; i++) {
        const union_definition* pUnion = union_vector[i];
        fprintf(pFP, "\t<li><a href=\"#%s\">%s</a></li>\n", pUnion->name().c_str(),pUnion->name().c_str());
    }
    fprintf(pFP, "</ul>\n");
    fprintf(pFP, "<hr>\n");
	for (size_t i = 0 ; i < size() ; i++) {
		const structure_definition*	pDef = (*this)[i];

        fprintf(pFP, "<a name=\"%s\" /><table border='1'>\n\t<caption>%s</caption>\n", pDef->name().c_str(), pDef->name().c_str());
        fprintf(pFP, "\t<tr><th>Offset</th><th>Type</th><th>Name</th></tr>\n");

        if (pDef->member_count() > 0) {
            for (int j = 0 ; j < pDef->member_count() ; j++) {
                const member_definition*	pMemb = pDef->member(j);

                if (pMemb->is_array()) {
                    char	sTmp[1024];
                    snprintf(sTmp, 1024, "%s[%ld]", pMemb->name().c_str(), (long)pMemb->maxindex());

                    fprintf(pFP, "\t<tr><td>%ld</td><td>%s</td><td>%s</td></tr>\n",
                        (long)pMemb->offset(),
                        pMemb->type().c_str(),
                        sTmp);
                } else {
                    fprintf(pFP, "\t<tr><td>%ld</td><td>%s</td><td>%s</td></tr>\n",
                        (long)pMemb->offset(),
                        pMemb->type().c_str(),
                        pMemb->name().c_str());
                }
            }
        }
        fprintf(pFP, "\t<tr><td colspan=\"2\">Total :</td><td>%ld</td></tr>\n", (long)pDef->size());
        fprintf(pFP, "</table><br>\n");
	}

	fprintf(pFP, "<hr>\n");
	for (size_t i = 0 ; i < union_vector.size() ; i++) {
		const union_definition*	pDef = union_vector[i];

        fprintf(pFP, "<a name=\"%s\" /><table border='1'>\n\t<caption>%s</caption>\n", pDef->name().c_str(), pDef->name().c_str());
        fprintf(pFP, "\t<tr><th>Offset</th><th>Type</th><th>Name</th></tr>\n");

        if (pDef->member_count() > 0) {
            for (int j = 0 ; j < pDef->member_count() ; j++) {
                const member_definition*	pMemb = pDef->member(j);

                if (pMemb->is_array()) {
                    char	sTmp[1024];
                    snprintf(sTmp, 1024, "%s[%ld]", pMemb->name().c_str(), (long)pMemb->maxindex());

                    fprintf(pFP, "\t<tr><td>%ld</td><td>%s</td><td>%s</td></tr>\n",
                        (long)pMemb->offset(),
                        pMemb->type().c_str(),
                        sTmp);
                } else {
                    fprintf(pFP, "\t<tr><td>%ld</td><td>%s</td><td>%s</td></tr>\n",
                        (long)pMemb->offset(),
                        pMemb->type().c_str(),
                        pMemb->name().c_str());
                }
            }
        }
        fprintf(pFP, "\t<tr><td colspan=\"2\">Total :</td><td>%ld</td></tr>\n", (long)pDef->size());
        fprintf(pFP, "</table><br>\n");
	}
    fprintf(pFP, "</body>\n</html>\n");

    fclose(pFP);
}
#endif  // _ENABLE_HTML_OUTPUT

#ifdef  _ENABLE_DUMP

void structure_database::dump(const char* szFileName) {
    FILE*   fp = 0L;

    fp = fopen(szFileName, "w");
    if (fp) {
        dump(fp);
    }
    fclose(fp);
    return;
}

void structure_database::dump(FILE* pHandle) {
    fprintf(pHandle, "There are %zu union definitions!\n", union_vector.size());

    for (size_t i = 0 ; i < union_vector.size() ; i++) {
		const union_definition*	pDef = union_vector[i];
        fprintf(pHandle, "Union %s [sizeof = %zu]\n", pDef->name().c_str(), pDef->size());

        if (pDef->member_count() > 0) {
            for (int j = 0 ; j < pDef->member_count() ; j++) {
                const member_definition*	pMemb = pDef->member(j);
                if (pMemb->is_array()) {
                    char	sTmp[1024];
                    snprintf(sTmp, 1024, "%s[%zu]", pMemb->name().c_str(), pMemb->maxindex());

                    fprintf(pHandle, "\t%-40s %-40s [%zu]\n",
                        pMemb->type().c_str(),
                        sTmp,
                        pMemb->offset());
                } else {
                    fprintf(pHandle, "\t%-40s %-40s [%zu]\n",
                        pMemb->type().c_str(),
                        pMemb->name().c_str(),
                        pMemb->offset());
                }
            }
        }

    }

	fprintf(pHandle, "There are %zu structures!\n", size());

	for (size_t i = 0 ; i < size() ; i++) {
		const structure_definition*	pDef = (*this)[i];

		fprintf(pHandle, "structure %s [sizeof = %zu]\n", pDef->name().c_str(), pDef->size());

        if (pDef->member_count() > 0) {
            for (int j = 0 ; j < pDef->member_count() ; j++) {
                const member_definition*	pMemb = pDef->member(j);

                if (pMemb->is_array()) {
                    char	sTmp[1024];
                    snprintf(sTmp, 1024, "%s[%zu]", pMemb->name().c_str(), pMemb->maxindex());

                    fprintf(pHandle, "\t[%-4zu] %-40s %-40s\n",
                        pMemb->offset(),
                        pMemb->type().c_str(),
                        sTmp);
                } else {
                    fprintf(pHandle, "\t[%-4zu] %-40s %-40s\n",
                        pMemb->offset(),
                        pMemb->type().c_str(),
                        pMemb->name().c_str());
                }
            }
        }
	}

    return;
}
#endif  // _ENABLE_DUMP

#ifdef  _ENABLE_EXCEL

/**
    libxls has a bug, will not generate a valid xls file for some reason...
 */

void structure_database::dump_xls(const char* szFilename, const char* szHeading) {
    workbook    wb;
    worksheet*   sh = wb.sheet("Structures");
    cell_t*     pCell;
    size_t      row = 0;

    sh->colwidth(0, 2560);
    sh->colwidth(1, 10240);
//    pCell = sh->label(0,0, "Structure Name");
//    pCell->fillfgcolor(CLR_GRAY25);
//    pCell->fontcolor(CLR_BLUE);
//    pCell->fillstyle(FILL_SOLID);
//
//    pCell = sh->label(0,1, "Structure Size");
//    pCell->fontcolor(CLR_BLUE);
//    pCell->fillfgcolor(CLR_GRAY25);
//    pCell->fillstyle(FILL_SOLID);

	for (size_t i = 0 ; i < size() ; i++) {
		const structure_definition*	pDef = (*this)[i];

//		fprintf(pHandle, "structure %s [sizeof = %d]\n", pDef->name().c_str(), pDef->size());

        pCell = sh->label(row, 0, pDef->name().c_str());
        pCell->fillfgcolor(CLR_GRAY25);
        pCell->fontcolor(CLR_BLUE);
        pCell->fillstyle(FILL_SOLID);
        pCell = sh->FindCellOrMakeBlank(row, 1);
        pCell->fillfgcolor(CLR_GRAY25);
        pCell->fontcolor(CLR_BLUE);
        pCell->fillstyle(FILL_SOLID);
        pCell = sh->number(row, 2, (signed32_t)pDef->size());
        pCell->fillfgcolor(CLR_GRAY25);
        pCell->fontcolor(CLR_BLUE);
        pCell->fillstyle(FILL_SOLID);

        row++;

        if (pDef->member_count() > 0) {
            for (int j = 0 ; j < pDef->member_count() ; j++) {
                const member_definition*	pMemb = pDef->member(j);

                if (pMemb->is_array()) {
                    char	sTmp[1024];
                    snprintf(sTmp, 1024, "%s[%d]", pMemb->name().c_str(), pMemb->maxindex());

                    pCell = sh->number(row, 0, (signed32_t)pMemb->offset());
                    pCell = sh->label(row, 1, pMemb->type().c_str());
                    pCell = sh->label(row, 2, sTmp);
//                    fprintf(pHandle, "\t[%-3d] %-40s %-40s\n",
//                        pMemb->offset(),
//                        pMemb->type().c_str(),
//                        sTmp);
                } else {
                    pCell = sh->number(row, 0, (signed32_t)pMemb->offset());
                    pCell = sh->label(row, 1, pMemb->type().c_str());
                    pCell = sh->label(row, 2, pMemb->name().c_str());
//                    fprintf(pHandle, "\t[%-3d] %-40s %-40s\n",
//                        pMemb->offset(),
//                        pMemb->type().c_str(),
//                        pMemb->name().c_str());
                }
                row++;
            }
        }
//        row++;
	}

//    sh->label(664, 0, "---");

    wb.Dump(szFilename);

    return;
}


#endif  // _ENABLE_EXCEL

void structure_database::push_state(int flag, void* data) {
    flagSt.push_back(flagPair(flag, data));
}

void structure_database::pop_state(int* flag, void** data) {
    flagPair    dataPair;

    dataPair = flagSt.back();
    if (flag != 0) {
        *flag = dataPair.first;
    }
    if (data != 0) {
        *data = dataPair.second;
    }
    flagSt.pop_back();
}

int structure_database::peek_state(void** data) {
    flagPair    dataPair;

    dataPair = flagSt.back();
    if (data != 0) {
        *data = dataPair.second;
    }
    return dataPair.first;
}

void structure_database::get_next_unnamed_struct(STRING& name) {
    char    sTmp[256];

//    snprintf(sTmp, 256, "Unnamed_Structure_%04d", unnamedIndex++);
    snprintf(sTmp, 256, "__STRUCT_%04d", unnamedStructIndex++);
    name = sTmp;
}

void structure_database::get_next_unnamed_union(STRING& name) {
    char    sTmp[256];

//    snprintf(sTmp, 256, "Unnamed_Structure_%04d", unnamedIndex++);
    snprintf(sTmp, 256, "__UNION_%04d", unnamedUnionIndex++);
    name = sTmp;
}

bool structure_database::init_regexp_parser() {
//	--	Compile the regular expression...
    D(debug("Compiling the regular expressions...\n"));

    if (add_regexp("^\\s*struct \(\\w+)\\s*\\{$", &exp_startstruct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*};$", &exp_endstruct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*struct\\s+(\\w+\\s*?\\*?)\\s+(\\w+);", &exp_membstruct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*struct\\s+(\\w+)\\s+(\\w+)\\[(.*)\\];", &exp_array_membstruct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*enum\\s+(\\w+)\\s+(\\w+)", &exp_membenum) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*(\\w+)\\s+(\\w+);", &exp_member) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*(\\w+)\\s+(\\w+)(\\[.*\\]);", &exp_array_member) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }

    if (add_regexp("^\\s*union\\s*([a-zA-Z0-9_]+)\\s*\\{", &exp_start_namedunion) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*struct\\s*\\{", &exp_memb_unnamed_struct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*\\}\\s+([a-zA-Z0-9_]+);", &exp_end_unnamed_struct) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }
    if (add_regexp("^\\s*union\\s*\\{", &exp_memb_unnamed_union) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }

    if (add_regexp("^\\s*union\\s+([a-zA-Z0-9_]+)\\s+([a-zA-Z0-9_]+)\\s*;", &exp_memb_union) == false) {
		fprintf(stderr, "ERROR: Unable to initialize regular expression parser!\n");
		return false;
    }

    return true;
}

void structure_database::release_regexp_parser() {
	D(debug("structure_database::release_regexp_parser()\n"));

    /* free all compiled regular expressions */
    for (size_t i = 0 ; i < m_reList.size() ; i++) {
        regfree(m_reList[i]);
    }
    m_reList.clear();

    return;
}

unsigned int structure_database::calculate_array_size(const char* szSize) {
    unsigned int    result = 1;
	STRING          sBuffer, sSubBuffer;

	//printf("calculate_array_size(%s)\n", szSize);

	sBuffer = szSize;

	for (size_t i = 0 ; i < sBuffer.size() ; i++) {
		if (sBuffer[i] == '[') {
			sSubBuffer.clear();
			i++;
			while (sBuffer[i] != ']') {
				sSubBuffer += sBuffer[i];
				i++;
			}
			sSubBuffer += '\n';
			//printf(" parsing expression %s\n", sSubBuffer.c_str());
			result *= parse_expression( sSubBuffer.c_str() );
		} else {
			sBuffer += '\n';
			//printf(" parsing expression %s\n", sBuffer.c_str());
			result = parse_expression( sBuffer.c_str() );
			i = sBuffer.size();
		}
	}

    D(debug("PARSING EXPRESSION %s = %d\n", szSize, result));
    return result;
}


bool structure_database::add_regexp(const char* sRegex, regex_t* expression) {
    int reError;

    D2(debug("structure_database::add_regexp(%s, 0x%08x)\n", sRegex, regcomp));

	if ((reError = regcomp(expression,  sRegex, REG_NEWLINE|REG_EXTENDED)) != 0) {
        char errBuff[256];
        D2(debug("ERROR: Unable to compile regular expression [%s]!\n", sRegex));

        if (regerror(reError, expression, errBuff, sizeof(errBuff))) {
            D2(debug("%s\n", errBuff));
//            m_sError = "Error : ";
            m_sError += errBuff;
        }

		return false;
	}

    /* push the compiled expression onto the vector */
    m_reList.push_back(expression);

    return true;
}


