/**
 * Copyright 2012 Lorin Beer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#import "PenderViewController.h"

/*
typedef struct {
    float Position[3];
    float Color[4];
} Vertex;
 
const Vertex Vertices[] = {
    {{1, -1, 0}, {1, 0, 0, 1}},
    {{1, 1, 0}, {0, 1, 0, 1}},
    {{-1, 1, 0}, {0, 0, 1, 1}},
    {{-1, -1, 0}, {0, 0, 0, 1}}
};
 
const GLubyte Indices[] = {
    0, 1, 2,
    2, 3, 0
};
*/
typedef struct {
    float Position[3];
    float Color[4];
    float TexCoord[2];
} Vertex;

const Vertex Vertices[] = {
    // Front
    {{1, -1, 1}, {1, 0, 0, 1}, {1, 0}},
    {{1, 1, 1}, {0, 1, 0, 1}, {1, 1}},
    {{-1, 1, 1}, {0, 0, 1, 1}, {0, 1}},
    {{-1, -1, 1}, {0, 0, 0, 1}, {0, 0}},
    // Back
    {{1, 1, -1}, {1, 0, 0, 1}, {0, 1}},
    {{-1, -1, -1}, {0, 1, 0, 1}, {1, 0}},
    {{1, -1, -1}, {0, 0, 1, 1}, {0, 0}},
    {{-1, 1, -1}, {0, 0, 0, 1}, {1, 1}},
    // Left
    {{-1, -1, 1}, {1, 0, 0, 1}, {1, 0}}, 
    {{-1, 1, 1}, {0, 1, 0, 1}, {1, 1}},
    {{-1, 1, -1}, {0, 0, 1, 1}, {0, 1}},
    {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}},
    // Right
    {{1, -1, -1}, {1, 0, 0, 1}, {1, 0}},
    {{1, 1, -1}, {0, 1, 0, 1}, {1, 1}},
    {{1, 1, 1}, {0, 0, 1, 1}, {0, 1}},
    {{1, -1, 1}, {0, 0, 0, 1}, {0, 0}},
    // Top
    {{1, 1, 1}, {1, 0, 0, 1}, {1, 0}},
    {{1, 1, -1}, {0, 1, 0, 1}, {1, 1}},
    {{-1, 1, -1}, {0, 0, 1, 1}, {0, 1}},
    {{-1, 1, 1}, {0, 0, 0, 1}, {0, 0}},
    // Bottom
    {{1, -1, -1}, {1, 0, 0, 1}, {1, 0}},
    {{1, -1, 1}, {0, 1, 0, 1}, {1, 1}},
    {{-1, -1, 1}, {0, 0, 1, 1}, {0, 1}}, 
    {{-1, -1, -1}, {0, 0, 0, 1}, {0, 0}}
};

const GLubyte Indices[] = {
    // Front
    0, 1, 2,
    2, 3, 0,
    // Back
    4, 6, 5,
    4, 5, 7,
    // Left
    8, 9, 10,
    10, 11, 8,
    // Right
    12, 13, 14,
    14, 15, 12,
    // Top
    16, 17, 18,
    18, 19, 16,
    // Bottom
    20, 21, 22,
    22, 23, 20
};



@implementation PenderViewController

@synthesize context = _context;
@synthesize effect = _effect;











- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    mView = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    mView.context = context;
    self.view = mView;
    
}


- (void)setupGL {
    
    [EAGLContext setCurrentContext:self.context];
    glEnable(GL_CULL_FACE);
    
    self.effect = [[GLKBaseEffect alloc] init];
    
    NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSNumber numberWithBool:YES],
                              GLKTextureLoaderOriginBottomLeft, 
                              nil];

    NSError * error;    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"tile_floor" ofType:@"png"];
    GLKTextureInfo * info = [GLKTextureLoader textureWithContentsOfFile:path options:options error:&error];
    if (info == nil) {
        NSLog(@"Error loading file: %@", [error localizedDescription]);
    }
    self.effect.texture2d0.name = info.name;
    self.effect.texture2d0.enabled = true;
    
    // New lines
    glGenVertexArraysOES(1, &_vertexArray);
    glBindVertexArrayOES(_vertexArray);
    
    // Old stuff
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    // New lines (were previously in draw)
    glEnableVertexAttribArray(GLKVertexAttribPosition);        
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(GLKVertexAttribColor);
    glVertexAttribPointer(GLKVertexAttribColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Color));
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, TexCoord));
    
    // New line
    glBindVertexArrayOES(0);
    
}

- (void)tearDownGL {
    
    [EAGLContext setCurrentContext:self.context];
    
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
    //glDeleteVertexArraysOES(1, &_vertexArray);
    
    self.effect = nil;    
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];

//    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

/*    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    */
    mView.drawableMultisample = GLKViewDrawableMultisample4X;
    [self setupGL];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    
    [self tearDownGL];

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
    glClearColor( 1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    [self.effect prepareToDraw];    
    
    glBindVertexArrayOES(_vertexArray);   
    glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, 0);
    
}

#pragma mark - GLKViewControllerDelegate

- (void)update {
    if (_increasing) {
        _curRed += 1.0 * self.timeSinceLastUpdate;
    } else {
        _curRed -= 1.0 * self.timeSinceLastUpdate;
    }
    if (_curRed >= 1.0) {
        _curRed = 1.0;
        _increasing = NO;
    }
    if (_curRed <= 0.0) {
        _curRed = 0.0;
        _increasing = YES;
    }
    
    float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 4.0f, 10.0f);    
    self.effect.transform.projectionMatrix = projectionMatrix;
    
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -6.0f);   
    _rotation += 90 * self.timeSinceLastUpdate;
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(25), 1, 0, 0);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, GLKMathDegreesToRadians(_rotation), 0, 1, 0);    
    self.effect.transform.modelviewMatrix = modelViewMatrix;
    
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    NSLog(@"timeSinceLastUpdate: %f", self.timeSinceLastUpdate);
    NSLog(@"timeSinceLastDraw: %f", self.timeSinceLastDraw);
    NSLog(@"timeSinceFirstResume: %f", self.timeSinceFirstResume);
    NSLog(@"timeSinceLastResume: %f", self.timeSinceLastResume);
    self.paused = !self.paused;
}




@end
