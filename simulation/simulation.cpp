#include "GLM/gtc/type_ptr.hpp"
#include <GLM/gtc/matrix_inverse.hpp>
#include <glad/gl.h>
#include "cs4722/view.h"
#include "cs4722/artifact.h"
#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/texture_utilities.h"
#include "learnopengl/shader.h"
#include "cs4722/light.h"

/*
Created on 05/22 by Kevin Galdamez
**********************************
This program is a simple OpenGL program
used to create a new scene. Note that the
cs4722 library is NOT mine. It was created
by Ben Setzer. Also note, this is my own
extension of a class assignment.
*/

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::artifact*> artifact_list;
static cs4722::light a_light;

static GLint ambient_light_loc; 
static GLint specular_light_loc;
static GLint diffuse_light_loc;
static GLint ambient_color_loc;
static GLint specular_color_loc;
static GLint diffuse_color_loc;
static GLint light_position_loc;
static GLint specular_shininess_loc;
static GLint specular_strength_loc;

static GLint m_transform_loc;
static GLint transform_loc, n_transform_loc;
static GLint sampler_loc;
static GLint sampler2_loc,samplerC_loc;
static GLint surface_effect_loc;
static GLint camera_position_loc;

static GLuint vao;

void init(){
    the_view = new cs4722::view();
    the_view->enable_logging = 0;
    the_view->set_flup(glm::vec3(0.202971,-0.227978,-0.952277),
                       glm::vec3(-0.978031,0,-0.20846),
                       glm::vec3(0.0475242,0.973667,-0.222969),
                       glm::vec3(-0.146291,0.195185,1.3214));
    a_light.ambient_light = cs4722::x11::gray25;
    a_light.light_direction_position = glm::vec4(0,1,0,0);
    a_light.is_directional = false;

    Shader shader("vertex_shader.glsl" ,"fragment_shader.glsl" );
    program = shader.ID;
    glUseProgram(program);

    ambient_light_loc = glGetUniformLocation(program, "ambient_light");
    specular_light_loc = glGetUniformLocation(program, "specular_light");
    diffuse_light_loc = glGetUniformLocation(program, "diffuse_light");
    ambient_color_loc = glGetUniformLocation(program, "ambient_color");
    specular_color_loc = glGetUniformLocation(program, "specular_color");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");
    light_position_loc = glGetUniformLocation(program, "light_position");
    specular_shininess_loc = glGetUniformLocation(program, "specular_shininess");
    specular_strength_loc = glGetUniformLocation(program, "specular_strength");

    m_transform_loc = glGetUniformLocation(program, "m_transform");
    transform_loc = glGetUniformLocation(program, "transform");
    n_transform_loc = glGetUniformLocation(program, "n_transform");
    sampler_loc = glGetUniformLocation(program, "sampler");
    sampler2_loc = glGetUniformLocation(program, "sampler2");
    samplerC_loc = glGetUniformLocation(program, "samplerC");
    surface_effect_loc = glGetUniformLocation(program, "surface_effect");
    camera_position_loc = glGetUniformLocation(program, "camera_position");
    vao = glGetUniformLocation(program, "vao");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    cs4722::init_texture_from_file("../media/sometexture.jpg", 2);
    cs4722::init_texture_computed(1, 128);
    cs4722::init_cube_texture_from_path("../media/oriented-cube", 10, "png");

    cs4722::shape* b = new cs4722::sphere(30, 30);
    auto* artf = new cs4722::artifact();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(-.65f, 0, 0));
    artf->world_transform.scale = (glm::vec3(.15f, .15f, .15f));
    artf->texture_unit = 2;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artf->surface_material.ambient_color = cs4722::x11::violet_red;
	artf->surface_material.specular_color = cs4722::x11::white;
	artf->surface_material.specular_strength = .75;
	artf->surface_material.shininess = 30.0;
    artifact_list.push_back(artf);

    b = new cs4722::sphere(30, 30);
    artf = new cs4722::artifact();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(.65f, 0, 0));
    artf->world_transform.scale = (glm::vec3(.15f, .15f, .15f));
    artf->texture_unit = 2;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artf->surface_material.ambient_color = cs4722::x11::violet_red;
	artf->surface_material.specular_color = cs4722::x11::white;
	artf->surface_material.specular_strength = .75;
	artf->surface_material.shininess = 30.0;
    artifact_list.push_back(artf);

    b = new cs4722::sphere(30, 30);
    artf = new cs4722::artifact();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(0, 0.65f, 0));
    artf->world_transform.scale = (glm::vec3(.15f, .15f, .15f));
    artf->texture_unit = 2;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artf->surface_material.ambient_color = cs4722::x11::violet_red;
	artf->surface_material.specular_color = cs4722::x11::white;
	artf->surface_material.specular_strength = .75;
	artf->surface_material.shininess = 30.0;
    artifact_list.push_back(artf);

    b = new cs4722::sphere(30, 30);
    artf = new cs4722::artifact();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(0, -0.65f, 0));
    artf->world_transform.scale = (glm::vec3(.15f, .15f, .15f));
    artf->texture_unit = 2;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artf->surface_material.ambient_color = cs4722::x11::violet_red;
	artf->surface_material.specular_color = cs4722::x11::white;
	artf->surface_material.specular_strength = .75;
	artf->surface_material.shininess = 30.0;
    artifact_list.push_back(artf);

    //tori use blend of diffuse color and texture
    cs4722::shape* b1 = new cs4722::torus(0.75,30,30);
    auto* artf2 = new cs4722::artifact_rotating();
    artf2->the_shape = (b1);
    artf2->world_transform.scale = (glm::vec3(.25f, .25f, .25f));
    artf2->animation_transform.rotation_axis = glm::vec3(0,1,0);
    artf2->animation_transform.rotation_center = glm::vec4(0,0,0,1);
    artf2->rotation_rate = -M_PI;
    artf2->texture_unit = 2;
    artf2->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf2->surface_effect = 0;
    artf2->surface_material.ambient_color = cs4722::x11::violet_red;
	artf2->surface_material.specular_color = cs4722::x11::white;
	artf2->surface_material.specular_strength = .75;
	artf2->surface_material.shininess = 30.0;
    artifact_list.push_back(artf2);
    
    b1 = new cs4722::torus(0.75,30,30);
    artf2 = new cs4722::artifact_rotating();
    artf2->the_shape = (b1);
    artf2->world_transform.scale = (glm::vec3(.75f, .75f, .75f));
    artf2->animation_transform.rotation_axis = glm::vec3(0,0,1);
    artf2->animation_transform.rotation_center = glm::vec4(0,0,0,1);
    artf2->rotation_rate = M_PI / 3;
    artf2->texture_unit = 2;
    artf2->surface_material.diffuse_color = cs4722::x11::slate_blue;
    artf2->surface_effect = 0;
    artf2->surface_material.ambient_color = cs4722::x11::slate_blue;
	artf2->surface_material.specular_color = cs4722::x11::white;
	artf2->surface_material.specular_strength = .75;
	artf2->surface_material.shininess = 30.0;
    artifact_list.push_back(artf2);

    auto skybox_scale = 40000.0f;
    auto* a_shape = new cs4722::block();
    auto artfb = new cs4722::artifact();
    artfb->the_shape = a_shape;
    artfb->world_transform.scale = glm::vec3(skybox_scale);
    artfb->texture_unit = 10;
    artfb->surface_effect = 4;
    artifact_list.push_back(artfb);

    cs4722::shape* b2 = new cs4722::torus(0.8,6,6);
    auto* artf3 = new cs4722::artifact();
    artf3->the_shape = (b2);
    artf3->world_transform.scale = (glm::vec3(1.15, 1.15, 1.15));
    artf3->world_transform.rotation_axis = glm::vec3(1,0,0);
    artf3->world_transform.rotation_center = glm::vec4(0,0,0,1);
    artf3->world_transform.rotation_angle = M_PI/2;
    artf3->world_transform.translate = (glm::vec3(0, -0.9f, 0));
    artf3->texture_unit = 10;
    artf3->surface_material.diffuse_color = cs4722::x11::slate_blue;
    artf3->surface_effect = 5;
    artf3->surface_material.ambient_color = cs4722::x11::slate_blue;
	artf3->surface_material.specular_color = cs4722::x11::white;
	artf3->surface_material.specular_strength = .75;
	artf3->surface_material.shininess = 30.0;
    artifact_list.push_back(artf3);

    vao = cs4722::init_buffers(program, artifact_list, "bPosition", "bColor", "bTextureCoord", "bNormal","");
}//end init

static GLfloat light_ambient[4];
static GLfloat light_diffuse[4];
static GLfloat light_specular[4];
static GLfloat material_ambient[4];
static GLfloat material_diffuse[4];
static GLfloat material_specular[4];

void display(){
    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;
    glUniform3fv(camera_position_loc, 1, glm::value_ptr(the_view->camera_position));
    glUniform4fv(light_position_loc, 1, glm::value_ptr(a_light.light_direction_position));

    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;
    for (auto artf : artifact_list) {
        artf->animate(time, delta_time);
        glm::mat4 model_transform = artf->animation_transform.matrix() * artf->world_transform.matrix();

        glm::mat4 n_transform = glm::inverseTranspose(model_transform);
        glUniformMatrix4fv(m_transform_loc, 1, GL_FALSE, glm::value_ptr(model_transform));
        glUniformMatrix4fv(n_transform_loc, 1, GL_FALSE, glm::value_ptr(n_transform));
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        if(artf->surface_effect == 4 || artf->surface_effect == 5) glUniform1i(samplerC_loc, artf->texture_unit);
        else glUniform1i(sampler_loc, artf->texture_unit);

        glUniform1i(surface_effect_loc, artf->surface_effect);
        glUniform4fv(diffuse_color_loc, 1, artf->surface_material.diffuse_color.as_float());
        a_light.ambient_light.as_float(light_ambient);
        a_light.diffuse_light.as_float(light_diffuse);
        a_light.specular_light.as_float(light_specular);
        artf->surface_material.ambient_color.as_float(material_ambient);
        artf->surface_material.diffuse_color.as_float(material_diffuse);
        artf->surface_material.specular_color.as_float(material_specular);
        glUniform4fv(ambient_light_loc, 1, light_ambient);
        glUniform4fv(diffuse_light_loc, 1, light_diffuse);
        glUniform4fv(specular_light_loc, 1, light_specular);
        glUniform4fv(ambient_color_loc, 1, material_ambient);
        glUniform4fv(diffuse_color_loc, 1,  material_diffuse);
        glUniform4fv(specular_color_loc, 1, material_specular);
        glUniform1f(specular_shininess_loc, artf->surface_material.shininess);
        glUniform1f(specular_strength_loc, artf->surface_material.specular_strength);
        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
    }//end for loop
}//end display

float speed = 0.025f;
static int old_width, old_height, old_xpos, old_ypos;
void general_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action != GLFW_PRESS && action != GLFW_REPEAT) return;
    else if (key == GLFW_KEY_A ) the_view->camera_position += speed * the_view->camera_left;
    else if (key == GLFW_KEY_D) the_view->camera_position -= speed * the_view->camera_left;
    else if (key == GLFW_KEY_W) the_view->camera_position += speed * the_view->camera_forward;
    else if (key == GLFW_KEY_S) the_view->camera_position -= speed * the_view->camera_forward;

    else if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_F11 && action == GLFW_PRESS){
        if (!glfwGetWindowMonitor(window)){
            glfwGetWindowPos(window, &old_xpos, &old_ypos);
            glfwGetWindowSize(window, &old_width, &old_height);
            auto monitor = glfwGetPrimaryMonitor();
            const auto* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }//end if statement
        else glfwSetWindowMonitor(window, nullptr, old_xpos, old_ypos, old_width, old_height, 0);
    }//end else if statement
}//end general_key_callback

void window_size_callback(GLFWwindow* window, int width, int height){
    int widthfb, heightfb;
    glfwGetFramebufferSize(window, &widthfb, &heightfb);
    glViewport(0, 0, widthfb, heightfb);
    the_view->perspective_aspect = (static_cast<float>(widthfb) / static_cast<float>(heightfb));
}//end window_size_callback


float lastX = 0, lastY = 0;
float yaw = -90.0f,pitch = 0;
void move_callback(GLFWwindow* window, double xpos, double ypos){
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;
    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    the_view->camera_forward = glm::normalize(direction);
    the_view->camera_left = glm::cross(the_view->camera_forward,glm::vec3(0,-1,0));
}//end move_callback


int main(int argc, char** argv){
    glfwInit();
    auto aspect_ratio = 16.0/9.0;
    auto* window = cs4722::setup_window("simulation", 0.9,aspect_ratio);
    gladLoadGL(glfwGetProcAddress);
    init();
    the_view->perspective_aspect = aspect_ratio;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetWindowUserPointer(window, the_view);
    glfwSetKeyCallback(window, general_key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetCursorPosCallback(window, move_callback);
    auto monitor = glfwGetPrimaryMonitor();
    const auto* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }//end while loop
    glfwDestroyWindow(window);
    glfwTerminate();
}//end main