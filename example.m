//
//  example.m
//  Objective-C-HMTL-Parser
//
//  Created by Jan on 27.11.12.
//
//

#import <Foundation/Foundation.h>

#import "HTMLParser.h"

#import "JXArcCompatibilityMacros.h"

int main(int argc, const char * argv[])
{
	
	@autoreleasepool {
		
		NSError *error = nil;
		NSString *html =
		@"<ul>"
		"<li><input type='image' name='input1' value='string1value' /></li>"
		"<li><input type='image' name='input2' value='string2value' /></li>"
		"</ul>"
		"<span class='spantext'><b>Hello World 1</b></span>"
		"<span class='spantext'><b>Hello World 2</b></span>";
		HTMLParser *parser = [[HTMLParser alloc] initWithString:html error:&error];
		
		if (error) {
			NSLog(@"Error: %@", error);
			return EXIT_FAILURE;
		}
		
		HTMLNode *bodyNode = [parser body];
		
		NSArray *inputNodes = [bodyNode findChildrenWithTag:@"input"];
		
		for (HTMLNode *inputNode in inputNodes) {
			if ([[inputNode getAttributeNamed:@"name"] isEqualToString:@"input2"]) {
				NSLog(@"%@", [inputNode getAttributeNamed:@"value"]); //Answer to first question
			}
		}
		
		NSArray *spanNodes = [bodyNode findChildrenWithTag:@"span"];
		
		for (HTMLNode *spanNode in spanNodes) {
			if ([[spanNode getAttributeNamed:@"class"] isEqualToString:@"spantext"]) {
				NSLog(@"%@", [spanNode rawContents]); //Answer to second question
			}
		}
		
		JX_RELEASE(parser);
		
	}
}