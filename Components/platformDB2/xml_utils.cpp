//#include "StdAfx.h"
//#include "libplatformdb.h"

#include "PlatformTypes.h"
#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
	WX_DEFINE_OBJARRAY(ArrayOfNodes);
#else
    #include <libxml/tree.h>
    #include <libxml/parser.h>
    #include <libxml/xmlmemory.h>
#endif
#include "xml_utils.h"
#include "dbg_utils.h"

#if !defined(__WXGTK__) && !defined(__WXMSW__)

#ifndef __WXDEBUG__
void print_element_names(XML_NODE_PTR a_node) {
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            //wxLogDebug("node type: Element, name: %s", cur_node->name);
        }

        print_element_names(cur_node->children);
    }
}
#endif

/**
	Find all child nodes which have the name sNodeName and append them to a
	vector of xml_node pointers.
 */

XML_NODE_PTR  find_child_node(XML_NODE_PTR pTopNode,
							const STRING& sNodeName,
							XMLNODE_VECTOR* pNodeVec)
{
	XML_NODE_PTR  pChild = pTopNode->children;
	XML_NODE_PTR  pResult = 0;

	if (pNodeVec)
		pNodeVec->clear();

	while (pChild) {
		if (pChild->type == XML_ELEMENT_NODE) {
			//D(//debug("comparing %s\n", pChild->name));
			/* if this is the node, return it! */
			if (sNodeName == (const char*)pChild->name) {
				if (pNodeVec == 0)
					return pChild;
				else {
					if (pResult == 0)
						pResult = pChild;
					pNodeVec->push_back(pChild);
				}
			}
		}
		pChild = pChild->next;
	}

	return pResult;
}

bool        get_node_contents_string(XML_NODE_PTR pNode, STRING& sString) {
    char*       sTmp;

    sTmp = (char *)xmlNodeGetContent(pNode);
    sString = sTmp;
    xmlFree(sTmp);

    return true;
}

bool        get_node_attribute_string(XML_NODE_PTR pNode, STRING sAttr, STRING& sString) {
    char*       sTmp;
    bool        result = true;

    sTmp = (char *)xmlGetProp( pNode, BAD_CAST (const char *)sAttr.c_str() );

    if (sTmp != 0) {
        sString = sTmp;
        xmlFree(sTmp);
    } else {
        sString.clear();
        result = false;
    }

    return result;
}


#else   // __WXGTK__

#ifdef __WXDEBUG__

void print_element_names(XML_NODE_PTR a_node) {
    XML_NODE_PTR cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->GetNext()) {
        if (cur_node->GetType() == wxXML_ELEMENT_NODE) {
            //wxLogDebug("node type: Element, name: %s", cur_node->GetName());
        }

        print_element_names(cur_node->GetChildren());
    }
}

#endif // __WXDEBUG_

/**
	Find all child nodes which have the name sNodeName and append them to a
	vector of xml_node pointers.
 */

XML_NODE_PTR  find_child_node(XML_NODE_PTR pTopNode,
							const STRING& sNodeName,
							XMLNODE_VECTOR* pNodeVec)
{
	XML_NODE_PTR  pChild = pTopNode->GetChildren();
	XML_NODE_PTR  pResult = 0;

	if (pNodeVec)
		pNodeVec->clear();

	while (pChild) {
		if (pChild->GetType() == wxXML_ELEMENT_NODE) {
			//D(//debug("comparing %s\n", pChild->name));
			/* if this is the node, return it! */

			if (sNodeName == (const char*)pChild->GetName()) {
				if (pNodeVec == 0)
					return pChild;
				else {
					if (pResult == 0)
						pResult = pChild;
					pNodeVec->push_back(pChild);
				}
			}
		}

		pChild = pChild->GetNext();
	}

	return pResult;
}

bool        get_node_contents_string(XML_NODE_PTR pNode, STRING& sString) {
    XML_NODE*  pChild = pNode->GetChildren();

    if (pChild) {
        sString = (const char *)pChild->GetContent().c_str();
        return true;
    }

    return false;
}

bool        get_node_attribute_string(XML_NODE_PTR pNode, STRING sAttr, STRING& sString) {
    STRING    value;

    if (pNode->GetAttribute(sAttr.c_str(), &value)) {
        sString = (const char *)value.c_str();
        return true;
    }

    return false;
}

/**
    Run through XML nodes looking for tag generating node array.

    @param tagName Name of tag to look for.
    @param rootNode Root node to begin search.
    @param tagArray Array of wxXmlNodes pointing to tag nodes.
    @return true if the tag was located.
 */

bool FindTags(wxString tagName, wxXmlNode* rootNode, ArrayOfNodes& tagArray) {
    wxXmlNode*  pNode;

//debug("FindTags(%s, ...)\n", tagName.c_str());

    pNode = rootNode->GetChildren();

    while (pNode != 0L) {
        if (pNode->GetName() == tagName) {
            tagArray.Add(*pNode);
        }
        pNode = pNode->GetNext();
    }

//debug("Found %d tags!\n", tagArray.GetCount());

    return ((tagArray.GetCount() > 0)?true:false);
}

/**
 *
 */

wxXmlNode* FindTag(wxString sTag, wxXmlNode* pRootNode) {
    wxXmlNode* pNode = 0L;

//  D(wxFprintf(stderr, "FindTag(%s, %p)\n", sTag, pRootNode));

    pNode = pRootNode->GetChildren();

    while (pNode != 0L) {
        if (pNode->GetName() == sTag) {
            return pNode;
        }
        pNode = pNode->GetNext();
    }

    return (wxXmlNode*)0L;
}

#endif  // __WXGTK__

