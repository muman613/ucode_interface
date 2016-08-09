#ifndef __PLATFORMTYPES_H__
#define __PLATFORMTYPES_H__

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/wx.h>
    #include <wx/hashmap.h>
    #include <wx/xml/xml.h>
#else
    #include <libxml/tree.h>
    #include <libxml/parser.h>
#endif

#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <list>

#ifdef	_WIN32
#if PLATFORMDB_EXPORTS
    #define DLLSPEC __declspec(dllexport)
	#define EXPIMP_TEMPLATE
#else
    #define DLLSPEC __declspec(dllimport)
	#define EXPIMP_TEMPLATE extern
#endif
#else
#define DLLSPEC
#define EXPIMP_TEMPLATE
#endif

#if (defined(__WXGTK__) || defined(__WXMSW__))
    typedef wxString                                STRING;
    typedef wxString                                string_t;
    typedef wxXmlNode                               XML_NODE;
    typedef wxXmlDocument *                         XML_DOC_PTR;
    typedef wxXmlNode *                             XML_NODE_PTR;
    WX_DECLARE_OBJARRAY(wxXmlNode, ArrayOfNodes);
#else   // __WXGTK__
    typedef xmlNode                                 XML_NODE;
    typedef xmlDoc *                                XML_DOC_PTR;
    typedef xmlNode *                               XML_NODE_PTR;
    typedef std::string 							STRING;
    typedef std::string                             string_t;
    typedef uint32_t                                wxUint32;
#endif  // __WXGTK__

/** vector of xmlnodes */
typedef std::vector<XML_NODE_PTR>	    		XMLNODE_VECTOR;
typedef std::vector<XML_NODE_PTR>::iterator     XMLNODE_VECTOR_ITER;

/** vector of strings */
typedef std::vector<STRING>				        STRING_VECTOR;
typedef std::vector<STRING>::iterator		    STRING_VECTOR_ITER;

/** map of environment strings to values */
typedef std::map<STRING,STRING>                 ENV_MAP;
typedef std::map<STRING,STRING>::iterator       ENV_MAP_ITER;
typedef std::pair<STRING,STRING>                ENV_PAIR;

/** map of symbol names to addresses */
typedef std::map<STRING, wxUint32>              SYMBOL_MAP;
typedef std::map<STRING, wxUint32>::iterator    SYMBOL_MAP_ITER;

typedef std::map<STRING, SYMBOL_MAP>            SEGMENT_MAP;
typedef std::map<STRING, SYMBOL_MAP>::iterator  SEGMENT_MAP_ITER;

/** vector of sourcecode lines */
typedef std::vector<STRING>			            SOURCELIST;
typedef std::vector<STRING>::iterator	        SOURCEITER;

typedef std::vector<int>                        INT_VECTOR;
typedef std::vector<int>::iterator              INT_VECTOR_ITER;

typedef std::pair<wxUint32, wxUint32>           REG_PAIR;
typedef std::vector<REG_PAIR>                   REG_PAIR_VECTOR;
typedef std::vector<REG_PAIR>::iterator         REG_PAIR_VECTOR_ITER;

typedef std::map<string_t, wxUint32>            ParameterMap;
typedef std::map<string_t, wxUint32>::iterator  ParameterMapIter;

typedef std::pair<STRING, STRING>               STRING_PAIR;
typedef std::vector<STRING_PAIR>                STRING_PAIR_VECTOR;

#endif // __PLATFORMTYPES_H__
