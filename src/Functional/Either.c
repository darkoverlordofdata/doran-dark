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
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include <dark/Functional/Either.h>
/**
 * Either `monad`
 * 
 * A container similar to a tuple [A, B]
 * Except that it can only contain A or B, not both.
 * By convention the right value (A) represents valid results
 * while the left value (B) represents an error condition.
 * 
 */
ivar (Either) {
	DSObject* left;
	DSObject* right;
	bool isLeft;
};

/**
 * Is it right or left?
 */
bool overload IsRight(Either* this) { 
	return !this->isLeft; 
}

/**
 * get the right member
 */
DSObject* overload GetRight(Either* this) { 
	return this->right; 
}

/**
 * get the left member
 */
DSObject* overload GetLeft(Either* this) { 
	return this->left; 
}

/**
 * Private constructor
 * Only Left & Right are allowed.
 */
static Either* NewEither(DSObject* a, DSObject* b) {
    const auto this = alloc(Either);
	this->left = a;
	this->right = b;
	this->isLeft = a != nullptr;
	return this;
}

/**
 * Left Public constructor
 */
Either* overload Left(DSObject* value) { 
	return NewEither(value, nullptr); 
}

/**
 * Right Public constructor
 */
Either* overload Right(DSObject* value) { 
	return NewEither(nullptr, value); 
}

Either* overload Map(Either* this, Either* (*func)(Either*)) {
	if (this->isLeft)
		return this;
	else
		return func(this);
}


