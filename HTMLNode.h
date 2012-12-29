//
//  HTMLNode.h
//  StackOverflow
//
//  Created by Ben Reeves on 09/03/2010.
//  Copyright 2010 Ben Reeves. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <libxml/HTMLparser.h>
#import "HTMLParser.h"

@class HTMLParser;

#define ParsingDepthUnlimited 0
#define ParsingDepthSame -1
#define ParsingDepth size_t

typedef enum
{
	HTMLHrefNode,
	HTMLTextNode,
	HTMLUnkownNode,
	HTMLCodeNode,
	HTMLSpanNode,
	HTMLPNode,
	HTMLLiNode,
	HTMLUlNode,
	HTMLImageNode,
	HTMLOlNode,
	HTMLStrongNode,
	HTMLPreNode,
	HTMLBlockQuoteNode,
} HTMLNodeType;

@interface HTMLNode : NSObject <NSCopying>
{
@public
	xmlNode * _node;
}

//Init with a lib xml node (shouldn't need to be called manually)
//Use [parser doc] to get the root Node
-(id)initWithXMLNode:(xmlNode*)xmlNode;

+(id)nodeWithName:(NSString *)name;

//Returns a single child of class
-(HTMLNode*)findChildOfClass:(NSString*)className;

//Returns all children of class
-(NSArray*)findChildrenOfClass:(NSString*)className;

//Finds a single child with a matching attribute 
//set allowPartial to match partial matches 
//e.g. <img src="http://www.google.com> [findChildWithAttribute:@"src" matchingName:"google.com" allowPartial:TRUE]
-(HTMLNode*)findChildWithAttribute:(NSString*)attribute
					  matchingName:(NSString*)className
					  allowPartial:(BOOL)partial;

//Finds all children with a matching attribute
-(NSArray*)findChildrenWithAttribute:(NSString*)attribute
						matchingName:(NSString*)className
						allowPartial:(BOOL)partial;

-(NSArray*)nodesForXPath:(NSString*)xpath;

//Gets the attribute value matching tha name
-(NSString*)getAttributeNamed:(NSString*)name;

-(void)setAttributeNamed:(NSString *)name withValue:(NSString *)value;

-(void)addAttributeNamed:(NSString *)name withValue:(NSString *)value;

-(void)removeAttributeNamed:(NSString *)name;

//Find children with the specified tag name
-(NSArray*)findChildrenWithTag:(NSString*)tagName;
-(NSArray*)findChildTags:(NSString*)tagName DEPRECATED_ATTRIBUTE;

//Looks for a tag name e.g. "h3"
-(HTMLNode*)findChildWithTag:(NSString*)tagName;
-(HTMLNode*)findChildTag:(NSString*)tagName DEPRECATED_ATTRIBUTE;

//Returns the first child element
-(HTMLNode*)firstChild;

//Returns the plaintext contents of node
-(NSString*)contents;

//Returns the plaintext contents of this node + all children
-(NSString*)allContents;

//Returns the html contents of the node 
-(NSString*)rawContents;

//Returns rawContents - surrounding tag
-(NSString*)innerHTML;

//Returns next sibling in tree
-(HTMLNode*)nextSibling;

//Returns previous sibling in tree
-(HTMLNode*)previousSibling;

//Returns the class name
-(NSString*)className;

//Returns the tag name
-(NSString*)tagName;

//Returns the parent
-(HTMLNode*)parent;

//Returns the first level of children
-(NSArray*)children;

//Returns the node type if know
-(HTMLNodeType)nodetype;


//C functions for minor performance increase in tight loops
NSString * getAttributeNamed(xmlNode * node, const char * nameStr);
void setAttributeNamed(xmlNode * node, const char * nameStr, const char * value);
HTMLNodeType nodeType(xmlNode* node);
NSString * allNodeContents(xmlNode*node);
NSString * rawContentsOfNode(xmlNode * node);

#pragma mark - Flip Studio mods

- (NSArray *)childrenForXPath:(NSString *)xpath;
- (void)setContent:(NSString *)content;
- (void)addNextSibling:(HTMLNode *)child;
- (void)addPrevSibling:(HTMLNode *)child;
- (void)addChild:(HTMLNode *)child;
- (void)removeFromParent;

@end
