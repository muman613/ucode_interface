#ifndef __XML_UTILS_H__
#define __XML_UTILS_H__

#if (defined(__WXGTK__) || defined(__WXMSW__))
#include <wx/wx.h>
#endif // __WXGTK__

#include "PlatformTypes.h"
#include "PlatformDatabase.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
bool            FindTags(wxString tagName, wxXmlNode* rootNode, ArrayOfNodes& tagArray);
wxXmlNode*      FindTag(wxString tagName, wxXmlNode* rootNode);
#else   // __WXGTK__
void            print_element_names(XML_NODE_PTR a_node);
XML_NODE_PTR    find_child_node(XML_NODE_PTR, const STRING&, XMLNODE_VECTOR*);
bool            get_node_contents_string(XML_NODE_PTR, STRING&);
bool            get_node_attribute_string(XML_NODE_PTR pNode, STRING sAttr, STRING& sString);
#endif // __WXGTK__

#endif  // __XML_UTILS_H__

