/*
    SwiffPath.h
    Copyright (c) 2011, musictheory.net, LLC.  All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of musictheory.net, LLC nor the names of its contributors
          may be used to endorse or promote products derived from this software
          without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL MUSICTHEORY.NET, LLC BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import <SwiffImport.h>

@class SwiffLineStyle, SwiffFillStyle;

enum {
    SwiffPathOperationEnd   = 0,
    SwiffPathOperationMove  = 1,  // Corresponds to 1 point  in -points : { CGPoint to }
    SwiffPathOperationLine  = 2,  // Corresponds to 1 point  in -points : { CGPoint to }
    SwiffPathOperationCurve = 3   // Corresponds to 2 points in -points : { CGPoint to, CGPoint control }
};
typedef UInt8 SwiffPathOperation;


@class SwiffPath;
extern void SwiffPathAddOperation(SwiffPath *path, SwiffPathOperation operation, const CGPoint *toPoint, const CGPoint *controlPoint);


@interface SwiffPath : NSObject {
@private
    NSUInteger      m_operationsCount;
    UInt8          *m_operations;

    NSUInteger      m_pointsCount;
    CGPoint        *m_points;

    SwiffLineStyle *m_lineStyle;
    SwiffFillStyle *m_fillStyle;
}

- (id) initWithLineStyle:(SwiffLineStyle *)lineStyle fillStyle:(SwiffFillStyle *)fillStyle;

/*
    operations              # points example data
    ----------------------- -------- -------------
    SwiffPathOperationMove  1        { 2.0, 3.0 }
    SwiffPathOperationLine  1        { 3.0, 3.0 }
    SwiffPathOperationCurve 2        { 4.0, 3.0 }
                                     { 4.0, 4.0 }
    SwiffPathOperationEnd   0
*/
@property (nonatomic, assign, readonly) NSUInteger operationsCount;
@property (nonatomic, assign, readonly) NSUInteger pointsCount;

@property (nonatomic, assign, readonly) UInt8   *operations; // Inside pointer, valid for lifetime of the SwiffPath
@property (nonatomic, assign, readonly) CGPoint *points;     // Inside pointer, valid for lifetime of the SwiffPath

@property (nonatomic, retain, readonly) SwiffLineStyle *lineStyle;
@property (nonatomic, retain, readonly) SwiffFillStyle *fillStyle;

@end