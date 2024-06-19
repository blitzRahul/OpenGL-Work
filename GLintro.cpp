//euclids theorem
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    while(!glfwWindowShouldClose(window)){
        //swapping buffers (double buffers)
        //as soon as we finish writing to the buffer we can swap to display it
        //seamless viewing
        //processInput(window);
        glClearColor(0.8f,0.8f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}