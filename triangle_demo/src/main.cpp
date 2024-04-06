#include <memory>
#include <xengine/app.hpp>
using namespace XEngine;

/// <summary>
/// Triangle example class.
/// </summary>
class Triangle : public Transform {
public:
    //Constructor.
    Triangle() : Transform(glm::vec3(0.f), glm::vec4(glm::vec3(0.f), 1.f), glm::vec3(1.f)) {}

    //Initialization method.
    void initialize() {
        //Initialize mesh.
        unsigned int vert_num = 3;
        float vertices[] = {
            //       POSITIONS                 NORMAL               UVs
                -0.5f, -0.5f,  0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
                 0.5f, -0.5f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
                 0.0f,  0.5f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f
        };
        //Enumerate indicies.
        std::vector<unsigned int> indicies(vert_num);
        for (unsigned int i = 0; i < vert_num; i++)
            indicies[i] = i;
        //Add mesh to render list.
        m_meshes.push_back(Mesh(Vertex::generate_list(vertices, vert_num), indicies));
        //Initialize base class.
        Transform::initialize();
    }

    //Rendering method.
    void render() {
        //Just call base class.
        Transform::render();
    }
};

Triangle triangle{};
Material mat;

class HelloWorldApp : public App {
    virtual void initialize() override {
        //Initialize material.
        mat.shader = Shader("res\\core.vert", "res\\core.frag");
        triangle.set_material(&mat);
        //Initialize triangle.
        triangle.initialize();
    }

    virtual void update() override {
        //Enable shader.
        mat.shader.enable();
        //Set position variable.
        mat.shader.set_3_floats("aPos", triangle.position);
        //Draw triangle.
        triangle.render();
    }

    virtual void on_shutdown() override {
        //Clean up shader.
        mat.remove();
        triangle.remove();
    }
};

int main() {
    //Create instance of app.
    auto app = std::make_unique<HelloWorldApp>();
    int returnC = app->start(800, 600, "Hello World!");
    return 0;
}
