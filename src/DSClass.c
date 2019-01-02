/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LI  ABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include <dark/DSClass.h>
#include <dark/DSLog.h>

/**
 * Load the class metadata
 * 
 * Classes must be loaded before they can be used
 */
void __attribute__((constructor(101))) DSClassBoot() 
{
    /** Initialize the runtime object system */

    /** Initialize the framework */
    DSClass = (struct DSClass) { 
        .isa            = &DSClass,
        .superclass     = &DSClass,
        .name           = "DSClass",
        .instance_size  = sizeof(DSClass),
    };

    DSClassList = (struct DSClassList) {
        .count          = 1, 
        .classes        = { &DSClass } 
    };

    objc_init();

    class_loadDSObject();
    class_loadDSComparable();
    class_loadDSCollection();
    class_loadDSArray();
    class_loadDSList();
    class_loadDSHashmap();
    class_loadDSBoolean();
    class_loadDSNumber();
    class_loadDSChar();
    class_loadDSDouble();
    class_loadDSFloat();
    class_loadDSInteger();
    class_loadDSLong();
    class_loadDSShort();
    class_loadDSString();
    class_loadDSStringBuilder();

    // for (int i=0; DSClass.classes[i] != nullptr; i++) {
    //     DSLog(class_isa(DSClass.classes[i])->name);
    // }

}

Class implement_DSClass(Class super) 
{
    Class obj = objc_allocateClassPair(super, "DSClass", 0);

}
/** 
 * The interface to objc_sendMessage:
 * 
 *      DSDictionary d* = _(_(DSDictionary, $alloc)$init); 
 *      _(d, $setObject, anObject, $forKey, $("foo"));
 * 
 *  In vala, call as:
 * 
 *  DSDictionary d* = _(_(DSDictionary, $alloc)$init);
 *  _(d, setObject: anObject, forKey: $("foo"));
 * 
 */
id _(id this, SEL _cmd, ...) {

}

