//-----------------------------------------------------------------------------
//  MODULE      :   structure_control.h
//  PROJECT     :   em8600_probe
//  PROGRAMMER  :   Michael A. Uman
//  DATE        :   June, 2009
//  COPYRIGHT   :   (C) 2005-2014 Sigma Designs
//-----------------------------------------------------------------------------

#ifndef __STRUCTURE_CONTROL_H__
#define __STRUCTURE_CONTROL_H__

#include <vector>
#include <string>
#include <tre/regex.h>

/* forward declarations */
class member_definition;
class structure_definition;
class structure_database;

/** structure control debug output options */
#define _ENABLE_HTML_OUTPUT         1
//#define _ENABLE_DUMP                1

/** Maximum length of a source line */
#define MAX_CMD     1024

/** flag macros */

#define FLAG_SET(var, flag)     (var |= flag)
#define FLAG_CLEAR(var, flag)   (var &= ~flag)
#define FLAG_ISSET(var, flag)   (var & flag)
#define FLAG_ISCLEAR(var, flag) ((var & flag) == 0)

#define MAKE_FLAG(bit)              (1L << bit)
#define FLAGS_NONE                  0
#define FLAGS_IN_STRUCT             MAKE_FLAG(0)
#define FLAGS_IN_UNION              MAKE_FLAG(1)
#define FLAGS_IN_UNNAMEDSTRUCT      MAKE_FLAG(2)
#define FLAGS_IN_UNNAMEDUNION       MAKE_FLAG(3)

typedef std::pair<int,void*>        flagPair;
typedef std::vector<flagPair>       flagStack;
typedef std::string                 STRING;

/**
    Class to contain structure member information
 */

class member_definition {
    public:
        member_definition(const char* member, const char* type, size_t offset = 0);
        member_definition(const char* member, const char* type, size_t index, size_t offset);
        member_definition(const member_definition& copy);
        ~member_definition();

        const STRING& name() const {
            return member_name;
        }
        const STRING& type() const {
            return member_type;
        }

        size_t offset() const {
            return member_offset;
        }

        bool is_array() const {
            return (member_flags & flag_array)?true:false;
        }

        size_t maxindex() const {
            return member_maxindex;
        }

    private:

        enum flags {
            flag_variable   = (1 << 0),
            flag_pointer    = (1 << 1),
            flag_array      = (1 << 2),
            flag_union      = (1 << 3),
        };

        STRING          member_name;
        STRING          member_type;
        size_t          member_offset;
        flags           member_flags;
        size_t          member_maxindex;
};

typedef std::vector<member_definition> MEMBER_VECTOR;


/**
    Class to contain structure defintion
 */

class structure_definition {
    public:
        structure_definition(structure_database* db, const char* name);
        ~structure_definition();

        const STRING& name() const {
            return struct_name;
        }

        /// Get the # of members in this structure
        int member_count() const {
            return members.size();
        }

        /// Get the size of the structure...
        size_t size() const {
            return last_offset;
        }

        const member_definition* operator[](int index) const {
            if ((size_t)index < members.size()) {
                return (const member_definition*)&members[index];
            } else {
                return (const member_definition*)0L;
            }
        }

        void add_member(const char* name, const char* type, size_t offset = 0);
        void add_member_size(const char* name, const char* type, size_t size);
        void add_array_member(const char* name, const char* type, int index, size_t offset = 0);
        void add_union_member(const char* name, const char* type, size_t offset = 0);

        const member_definition* member(const char* member) const;
        const member_definition* member(int index) const;

    protected:
//      size_t  get_type_size(const char* type);

    private:
        structure_database*     struct_db;
        STRING              struct_name;
        MEMBER_VECTOR           members;
        size_t                  last_offset;

};

typedef std::vector<structure_definition*>  STRUCTURE_VECTOR;

//==============================================================================
//==============================================================================

class union_definition {
    public:
        union_definition(structure_database* db, const char* name);
        ~union_definition();

        const STRING& name() const {
            return struct_name;
        }

        int member_count() const {
            return members.size();
        }

        size_t size() const {
            return last_offset;
        }

        const member_definition* operator[](int index) const {
            if ((size_t)index < members.size()) {
                return (const member_definition*)&members[index];
            } else {
                return (const member_definition*)0L;
            }
        }

        void add_member(const char* name, const char* type, size_t offset = 0);
        void add_array_member(const char* name, const char* type, int index, size_t offset = 0);

        const member_definition* member(const char* member) const;
        const member_definition* member(int index) const;

    protected:
//      size_t  get_type_size(const char* type);

    private:
        structure_database*     struct_db;
        STRING              struct_name;
        MEMBER_VECTOR           members;
        size_t                  last_offset;

};

typedef std::vector<union_definition*>  UNION_VECTOR;

/**
    Class to store structure database in.
 */

class structure_database {
    public:
        structure_database();
        ~structure_database();

        size_t size() const {
            return structure_vector.size();
        }

        size_t get_union_size(const char* type);
        size_t get_type_size(const char* type);

        structure_definition*       new_structure(const char* name);
        union_definition*           new_union(const char* name);

        const structure_definition* operator[](int index) const {
            if ((size_t)index < structure_vector.size()) {
                return (const structure_definition*)structure_vector[index];
            } else {
                return (const structure_definition*)0L;
            }
        }

        const structure_definition* get_structure(const char* struct_name);
        const union_definition*     get_union(const char* union_name);

        bool                    open(const char* filename);
        void                    reset();
        void                    sort_structures();

        /* dump functions */

#ifdef  _ENABLE_DUMP
        void                    dump(const char* szFilename);
        void                    dump(FILE* pHandle);
#endif

#ifdef  _ENABLE_HTML_OUTPUT
        void                    dump_html_table(const char* szFileName, const char* szHeading = 0L);
#endif

#ifdef  _ENABLE_EXCEL
        void                    dump_xls(const char* szFileName, const char* szHeading = 0L);
#endif

    private:
        FILE*                   ifp;

        bool                    parse_file(const char* filename);

        STRUCTURE_VECTOR        structure_vector;
        UNION_VECTOR            union_vector;

        regex_t                 exp_startstruct, exp_endstruct,
                                exp_membstruct, exp_array_membstruct,
                                exp_membenum, exp_array_member, exp_member;

        regex_t                 exp_memb_unnamed_struct;
        regex_t                 exp_start_namedunion;
        regex_t                 exp_end_unnamed_struct;
        regex_t                 exp_memb_unnamed_union;
        regex_t                 exp_memb_union;

        flagStack               flagSt;

        void                    push_state(int flag, void* data);
        void                    pop_state(int* flag = 0,void** data = 0L);
        int                     peek_state(void** data = 0L);

        void                    get_next_unnamed_struct(STRING& name);
        void                    get_next_unnamed_union(STRING& name);

        int                     unnamedStructIndex, unnamedUnionIndex;

        bool                    init_regexp_parser();
        void                    release_regexp_parser();
        unsigned int            calculate_array_size(const char* szSize);

        std::vector<regex_t*>   m_reList;   /// vector of regular expressions

        bool                    add_regexp(const char* sRegex, regex_t* expression);

        STRING             m_sError;
};



#endif  // __STRUCTURE_CONTROL_H__

