//euclids theorem
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <math.h>

//vertex shader code
//layout location 0 is basically telling vert shader the location of the input varialble
//in will place the vertex data into aPos
//gl_Position is a predefined vec4 behind the scenes which is used to store the output of the vertex shader
 const char *vertexShaderSource = "#version 330 core\n"
 "layout (location = 0) in vec3 aPos;\n"
 "layout (location = 1) in vec3 vertexColor;\n"
 "out vec4 ourColor;\n"
 "void main()\n"
 "{\n"
 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
 "ourColor=vec4(aPos,1.0f);\n"
 "}\0";


 //source of the fragment shader
 /*
 #version 330 core
 out vec4 FragColor;
 void main()
 {
 FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
 }
 */
 const char* fragmentShaderSource="#version 330 core\n"
 "in vec3 aPos;\n"
 "in vec4 ourColor;\n"
 "out vec4 FragColor;\n"
 "//uniform vec4 ourColor;\n"
 "void main()\n"
 "{\n"
 "FragColor=ourColor;\n"
 "}\0";


void getVertexShaderFile(char* fileName, std::string &yes){

}

void resizeViewport_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void keyPressCallback(GLFWwindow* window, int key, int action, int scancode, int mod){
std::cout<<"key was pressed: "<<(int)key<<std::endl;
if(key==256){
    glfwSetWindowShouldClose(window,true);
}
}

//another way of processing immediate input. call this inside of the main loop
void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        //do something
    }
}

void simpleTransform(float* coordinates, int size, float posOffset){
    for(int i=0;i<size;i+=3){
        *coordinates+=posOffset;
        coordinates+=3;
    }
} 

//sets the position of X coordinates of each vertex
void XTransform(float* coordinates, int size, float posOffset){
    for(int i=0;i<size;i+=3){
        *coordinates+=posOffset;
        coordinates+=3;
    }
} 

//changes per vertex color
void changeColor(float* vertexData,int size, float* colorData){
    int ctr=size/6;
    vertexData+=3;
    while(ctr!=0){
        
        memcpy(vertexData,colorData,3*sizeof(float));
        colorData+=3;
        vertexData+=6;
        ctr-=1;
    }
}

int main(){
    //initialize glfw
    glfwInit();
    //set major version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    //also set minor version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //set the profile to core only, will get rid of backwards compatible stuff and will only stick to version 3.3  stuff
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //creating the context
    GLFWwindow* window = glfwCreateWindow(800,600,"fuck this class",NULL,NULL);
    if(window==NULL){

        std::cout<<"context and window creation failed"<<std::endl;
        glfwTerminate();
    }
    //making the context current. remeber openGL is a big statemachine, all the stuff is going to be written to this
    glfwMakeContextCurrent(window);
    //passing glad glfwGetProcAddress (this is windows specific)
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"tried passing glfwGetProcAddress but failed"<<std::endl;
        return -1;
    }

    //setting viewport dimensions and bottom coordinates.... dimx = 800 dimy= 600
    glViewport(0,0,800,600);
    //setting frame buffer resize callback
    glfwSetFramebufferSizeCallback(window,resizeViewport_callback);
   // glfwSetKeyCallback(window,);
    glfwSetKeyCallback(window,keyPressCallback);
    
    //creating a shader object and storing its id for later reference
    unsigned int vertexShaderId;
    vertexShaderId=glCreateShader(GL_VERTEX_SHADER);
    //setting the source code of the shader
    glShaderSource(vertexShaderId,1,&vertexShaderSource,NULL);
    //compiling the shader
    glCompileShader(vertexShaderId);
    //checking if the compilation was a success
    int success;
    char infoLog[512];
    //this func returns the value of a parameter of the shader object
    glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShaderId,512,NULL,infoLog);
        std::cout<<"VERTEX Compilation failed for the following reason: \n";
        std::cout<<infoLog<<std::endl;
    }else{
        std::cout<<"VERTEX shader compilation succeeded"<<std::endl;
    }
        //creating a shader object and storing its id for later reference
    unsigned int fragmentShaderId;
    fragmentShaderId=glCreateShader(GL_FRAGMENT_SHADER);
    //setting the source code of the shader
    glShaderSource(fragmentShaderId,1,&fragmentShaderSource,NULL);
    //compiling the shader
    glCompileShader(fragmentShaderId);
    //checking if the compilation was a success
    
    //this func returns the value of a parameter of the shader object
    glGetShaderiv(fragmentShaderId,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderId,512,NULL,infoLog);
        std::cout<<"FRAGMENT Compilation failed for the following reason: \n";
        std::cout<<infoLog<<std::endl;
    }else{
        std::cout<<"FRAGMENT shader compilation succeeded"<<std::endl;
    }

    //creating a shader program object
    unsigned int shaderProgramId;
    shaderProgramId=glCreateProgram();
    glAttachShader(shaderProgramId,vertexShaderId);
    glAttachShader(shaderProgramId,fragmentShaderId);
    glLinkProgram(shaderProgramId);
    glUseProgram(shaderProgramId);

            float vertices[]={
            -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
            0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
            0.0f,0.5f,0.0f,0.0f,0.0f,1.0f 
        };
        //simpleTransform(vertices,12,-0.25);
        unsigned int indices[]={
        0,1,2
        };
        unsigned int VBOid;
        unsigned int VAOid;
        unsigned int EBOid;
        //this gives you an unused buffer index




        //https://stackoverflow.com/questions/11821336/what-are-vertex-array-objects


        glGenVertexArrays(1,&VAOid);
        glBindVertexArray(VAOid);
        glGenBuffers(1,&VBOid);
        //this actually creates the object there of the type
        glBindBuffer(GL_ARRAY_BUFFER,VBOid);
        glGenBuffers(1,&EBOid);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBOid);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        //write into the previously created targe
        //first param is what type is our target
        //vertex buffers are supposed to be of the type GL_ARRAY_BUFFER
        //STATIC_DRAW is bascially memory management stuff. STATIC DRAW means that this data does not change
        //so it can be stored in memory that is fast for reads
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        glUseProgram(shaderProgramId);
        glBindVertexArray(VAOid);
    while(!glfwWindowShouldClose(window)){
        //swapping buffers (double buffers)
        //as soon as we finish writing to the buffer we can swap to display it
        //seamless viewing
        //processInput(window);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

     
         float timeValue = glfwGetTime();
         float greenColor= (sin(timeValue)/2)+0.5f;
         float redColor=(sin(timeValue+90)/2)+0.5f;
         float blueColor=(sin(timeValue+180)/2)+0.5f;
         //int vertexColorLocation= glGetUniformLocation(shaderProgramId,"ourColor");
         //passing uniform from CPU
        //glUniform4f(vertexColorLocation,redColor,greenColor,blueColor,1.0f);
        //type of primitive
        //XTransform(vertices,12,sin(timeValue)/100.0f);
        //
        float colors[]={redColor,greenColor,blueColor,blueColor,greenColor,redColor,greenColor,redColor,blueColor};
        changeColor(vertices,18,colors);
        //updating the GL_ARRAY_BUFFER target with the current vertex data
        //glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}