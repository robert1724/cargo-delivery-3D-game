#include "lab_m1/tema2/tema2.h"
#include "lab_m1/lab5/lab_camera.h"


#include <iostream>
#include <glm/geometric.hpp>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}


//creez formele de care ma voi folosi in scena
Mesh* create_square(const char* name, float x, glm::vec3 color) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-x, 0, -x), color),
        VertexFormat(glm::vec3(x, 0, -x), color),
        VertexFormat(glm::vec3(x, 0,  x), color),
        VertexFormat(glm::vec3(-x, 0,  x), color),
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    Mesh* quad = new Mesh(name);
    quad->InitFromData(vertices, indices);
    return quad;
}

Mesh* create_rectangle(const char* name, float width, float depth, glm::vec3 color) {
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-width, 0, -depth), color),
        VertexFormat(glm::vec3(width, 0, -depth), color),
        VertexFormat(glm::vec3(width, 0,  depth), color),
        VertexFormat(glm::vec3(-width, 0,  depth), color),
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    Mesh* quad = new Mesh(name);
    quad->InitFromData(vertices, indices);
    return quad;
}

Mesh* create_circle(const char* name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {
    
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i <= 50; i++) {
        float angle = 2 * M_PI * i / 50;
        float x = center.x + radius * cos(angle);
        float z = center.z + radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, center.y, z), color));
    }

    for (int i = 1; i <= 50; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* create_box(const char* name, float size, glm::vec3 color) {
    
    float h = size / 2.0f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-h, -h,  h), color),
        VertexFormat(glm::vec3(h, -h,  h), color),
        VertexFormat(glm::vec3(h,  h,  h), color),
        VertexFormat(glm::vec3(-h,  h,  h), color),

        VertexFormat(glm::vec3(-h, -h, -h), color),
        VertexFormat(glm::vec3(h, -h, -h), color),
        VertexFormat(glm::vec3(h,  h, -h), color),
        VertexFormat(glm::vec3(-h,  h, -h), color),
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,   0, 2, 3,
        1, 5, 6,   1, 6, 2,
        5, 4, 7,   5, 7, 6,
        4, 0, 3,   4, 3, 7,
        3, 2, 6,   3, 6, 7,
        4, 5, 1,   4, 1, 0
    };

    Mesh* box = new Mesh(name);
    box->InitFromData(vertices, indices);
    return box;
}

Mesh* create_paralelipiped(const char* name, float width, float height, float depth, glm::vec3 color) {

    float hx = width / 2.0f;
    float hy = height / 2.0f;
    float hz = depth / 2.0f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-hx, -hy,  hz), color),
        VertexFormat(glm::vec3(hx, -hy,  hz), color),
        VertexFormat(glm::vec3(hx,  hy,  hz), color),
        VertexFormat(glm::vec3(-hx,  hy,  hz), color),
        VertexFormat(glm::vec3(-hx, -hy, -hz), color),
        VertexFormat(glm::vec3(hx, -hy, -hz), color),
        VertexFormat(glm::vec3(hx,  hy, -hz), color),
        VertexFormat(glm::vec3(-hx,  hy, -hz), color),
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,   0, 2, 3,
        1, 5, 6,   1, 6, 2,
        5, 4, 7,   5, 7, 6,
        4, 0, 3,   4, 3, 7,
        3, 2, 6,   3, 6, 7,
        4, 5, 1,   4, 1, 0
    };

    Mesh* box = new Mesh(name);
    box->InitFromData(vertices, indices);
    return box;
}

Mesh* create_cilindru(const char* name, float radius, float length, int segments, glm::vec3 color) {

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float h = length / 2.0f;

    int left = 0;
    int right = 1;

    vertices.push_back(VertexFormat(glm::vec3(-h, 0, 0), color));
    vertices.push_back(VertexFormat(glm::vec3(h, 0, 0), color));

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float y = radius * cos(angle);
        float z = radius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(-h, y, z), color));
        vertices.push_back(VertexFormat(glm::vec3(h, y, z), color));
    }

    for (int i = 0; i < segments; i++) {
        int base = 2 + i * 2;

        int l0 = base;
        int r0 = base + 1;
        int l1 = base + 2;
        int r1 = base + 3;

        indices.push_back(l0);
        indices.push_back(r0);
        indices.push_back(l1);

        indices.push_back(l1);
        indices.push_back(r0);
        indices.push_back(r1);

        indices.push_back(left);
        indices.push_back(l0);
        indices.push_back(l1);

        indices.push_back(right);
        indices.push_back(r1);
        indices.push_back(r0);
    }

    Mesh* cilindru = new Mesh(name);
    cilindru->InitFromData(vertices, indices);
    return cilindru;
}

Mesh* create_sphere(const char* name, float radius, int stacks, int sectors, glm::vec3 color) {

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= stacks; i++) {
        float v = (float)i / stacks;
        float pi = M_PI * v;

        for (int j = 0; j <= sectors; j++) {
            float u = (float)j / sectors;
            float theta = 2 * M_PI * u;

            float x = radius * sin(pi) * cos(theta);
            float y = radius * cos(pi);
            float z = radius * sin(pi) * sin(theta);

            vertices.push_back(
                VertexFormat(glm::vec3(x, y, z), color)
            );
        }
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < sectors; j++) {
            int first = i * (sectors + 1) + j;
            int second = first + sectors + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    Mesh* sphere = new Mesh(name);
    sphere->InitFromData(vertices, indices);
    return sphere;
}

Mesh* create_pyramid(const char* name, float baseSize, float height, glm::vec3 color) {
    
    float h = baseSize / 2.0f;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-h, 0.0f, -h), color),
        VertexFormat(glm::vec3(h, 0.0f, -h), color),
        VertexFormat(glm::vec3(h, 0.0f,  h), color),
        VertexFormat(glm::vec3(-h, 0.0f,  h), color),
        VertexFormat(glm::vec3(0.0f, height, 0.0f), color)
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    Mesh* pyramid = new Mesh(name);
    pyramid->InitFromData(vertices, indices);
    return pyramid;
}

Mesh* create_donut(const char* name, float majorRadius, float minorRadius, int majorSegments, int minorSegments, glm::vec3 color) {
    
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= majorSegments; i++) {
        float u = (float)i / majorSegments;
        float theta = 2.0f * (float)M_PI * u;

        float cosT = cos(theta);
        float sinT = sin(theta);

        for (int j = 0; j <= minorSegments; j++) {
            float v = (float)j / minorSegments;
            float phi = 2.0f * (float)M_PI * v;

            float cosP = cos(phi);
            float sinP = sin(phi);

            float x = (majorRadius + minorRadius * cosP) * cosT;
            float y = minorRadius * sinP;
            float z = (majorRadius + minorRadius * cosP) * sinT;

            vertices.push_back(VertexFormat(glm::vec3(x, y, z), color));
        }
    }

    int ring = minorSegments + 1;
    for (int i = 0; i < majorSegments; i++) {
        for (int j = 0; j < minorSegments; j++) {
            int a = i * ring + j;
            int b = (i + 1) * ring + j;
            int c = a + 1;
            int d = b + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);

            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(d);
        }
    }

    Mesh* torus = new Mesh(name);
    torus->InitFromData(vertices, indices);
    return torus;
}


void Tema2::Init()
{
    //initializarea camerei pentru a incadra toata scena
    camera = GetSceneCamera();
    GetCameraInput()->SetActive(true);
    glm::vec3 eye = glm::vec3(0, 10, 7.25);
    glm::vec3 target = glm::vec3(0, 0, 16);
    glm::vec3 up = glm::vec3(0, 1, 0);
    camera->SetPosition(eye);
    glm::vec3 dir = glm::normalize(target - eye);
    float yaw = atan2(dir.x, dir.z);
    float pitch = asin(dir.y);
    camera->SetRotation(glm::vec3(pitch, yaw, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    //scena 2D compusa din quad-uri
    Mesh* grass = create_square("grass", 100.0f, glm::vec3(0.45f, 0.85f, 0.35f));
    Mesh* water1 = create_rectangle("water1", 0.25f, 1.0f, glm::vec3(0.3, 0.7, 0.9));
    Mesh* water2 = create_rectangle("water2", 1.0f, 0.25f, glm::vec3(0.3, 0.7, 0.9));
    Mesh* lake = create_circle("lake", glm::vec3(0, 0.01f, 0), 2.0f, glm::vec3(0.3, 0.7, 0.9), true);
    Mesh* mountain1 = create_rectangle("mountain1", 2.25f, 3.5f, glm::vec3(0.35f, 0.25f, 0.20f));
    Mesh* mountain2 = create_rectangle("mountain2", 1.25f, 1.75f, glm::vec3(0.4f, 0.3f, 0.25f));
    Mesh* station1 = create_box("box", 1.25f, glm::vec3(0.95f, 0.3f, 0.6f));
    Mesh* small_station1 = create_box("small_box", 0.875f, glm::vec3(0.95f, 0.3f, 0.6f));
	//cuantificator de timp -- culorile sferei se schimba in functie de timpul petrecut in joc
    Mesh* station2 = create_sphere("sphere_0", 0.5f, 20, 20, glm::vec3(1.00f, 0.96f, 0.65f));
    Mesh* station2_1 = create_sphere("sphere_1", 0.5f, 20, 20, glm::vec3(1.00f, 0.92f, 0.5f));
    Mesh* station2_2 = create_sphere("sphere_2", 0.5f, 20, 20, glm::vec3(1.00f, 0.88f, 0.35f));
    Mesh* station2_3 = create_sphere("sphere_3", 0.5f, 20, 20, glm::vec3(1.00f, 0.82f, 0.15f));
    Mesh* station2_4 = create_sphere("sphere_4", 0.5f, 20, 20, glm::vec3(1.00f, 0.72f, 0.08f));
    Mesh* station2_5 = create_sphere("sphere_5", 0.5f, 20, 20, glm::vec3(1.00f, 0.62f, 0.00f));
    Mesh* station2_6 = create_sphere("sphere_6", 0.5f, 20, 20, glm::vec3(1.00f, 0.5f, 0.00f));
    Mesh* station2_7 = create_sphere("sphere_7", 0.5f, 20, 20, glm::vec3(1.00f, 0.38f, 0.00f));
    Mesh* station2_8 = create_sphere("sphere_8", 0.5f, 20, 20, glm::vec3(1.00f, 0.25f, 0.05f));
    Mesh* station2_9 = create_sphere("sphere_9", 0.5f, 20, 20, glm::vec3(1.00f, 0.15f, 0.05f));
    Mesh* station2_10 = create_sphere("sphere_10", 0.5f, 20, 20, glm::vec3(1.00f, 0.07f, 0.02f));
    Mesh* station2_11 = create_sphere("sphere_11", 0.5f, 20, 20, glm::vec3(1.00f, 0.00f, 0.00f));
    // "small stations" vor fi echivalente cu ceea ce gara centrala va cere
    Mesh* station3 = create_pyramid("pyramid", 1.0f, 1.0f, glm::vec3(1.0f, 0, 0));
    Mesh* small_station3 = create_pyramid("small_pyramid", 0.7f, 0.7f, glm::vec3(1.0f, 0, 0));
    Mesh* station4 = create_donut("torus", 0.4f, 0.2f, 30, 30, glm::vec3(0.8f, 0.2f, 1.0f));
    Mesh* small_station4 = create_donut("small_torus", 0.28f, 0.14f, 30, 30, glm::vec3(0.8f, 0.2f, 1.0f));
    //sinele de tren
    Mesh* track_vertical = create_rectangle("track_vertical", 0.2f, 0.4f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* track_horizontal = create_rectangle("track_horizontal", 0.4f, 0.2f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* tunnel_navy_horizontal = create_rectangle("tunnel_navy_horizontal", 0.05f, 0.2f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* tunnel_white_horizontal = create_rectangle("tunnel_white_horizontal", 0.05f, 0.2f, glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh* tunnel_navy_vertical = create_rectangle("tunnel_navy_vertical", 0.2f, 0.05f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* tunnel_white_vertical = create_rectangle("tunnel_white_vertical", 0.2f, 0.05f, glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh* bridge_navy1 = create_rectangle("bridge_navy1", 0.4f, 0.04f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* bridge_white1 = create_rectangle("bridge_white1", 0.4f, 0.04f, glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh* bridge_navy2 = create_rectangle("bridge_navy2", 0.04f, 0.4f, glm::vec3(0.02f, 0.05f, 0.2f));
    Mesh* bridge_white2 = create_rectangle("bridge_white2", 0.04f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh* paralelipiped_verde = create_paralelipiped("paralelipiped_verde", 0.5f, 0.5f, 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    Mesh* paralelipiped_verde_vagon = create_paralelipiped("paralelipiped_verde_vagon", 0.5f, 0.5f, 1.2f, glm::vec3(0.0f, 1.0f, 0.0f));
    Mesh* paralelipiped_galben = create_paralelipiped("paralelipiped_galben", 0.5f, 0.1f, 1.2f, glm::vec3(1.0f, 1.0f, 0.0f));
    Mesh* box_pink = create_box("box_pink", 0.03f, glm::vec3(1.00f, 0.2f, 0.6f));
    Mesh* cilindru_albastru = create_cilindru("cilindru_albastru", 0.15f, 0.7f, 30, glm::vec3(0.0f, 0.0f, 1.0f));
    Mesh* cilindru_rosu = create_cilindru("cilindru_rosu", 0.08f, 0.08f, 30, glm::vec3(1.0f, 0.0f, 0.0f));
    Mesh* paralelipiped_negru = create_paralelipiped("paralelipiped_negru", 0.1f, 0.1f, 0.26f, glm::vec3(0.0f, 0.0f, 1.0f));
    //borders
    Mesh* zid_negru_v = create_paralelipiped("zid_negru_v", 1.0f, 1.0f, 30.0f, glm::vec3(0.1f, 0.1f, 0.1f));
    Mesh* zide_negru_h = create_paralelipiped("zid_negru_h", 30.0f, 1.0f, 1.0f, glm::vec3(0.1f, 0.1f, 0.1f));
    //muntii 3D
    Mesh* brown_mountain1 = create_pyramid("brown_mountain1", 5.0f, 4.0f, glm::vec3(0.35f, 0.25, 0.20));
    Mesh* brown_mountain2 = create_pyramid("brown_mountain2", 3.0f, 3.0f, glm::vec3(0.4f, 0.3f, 0.25));
    Mesh* brown_mountain3 = create_pyramid("brown_mountain3", 4.0f, 5.5f, glm::vec3(0.38f, 0.28f, 0.22));
    Mesh* black_screen = create_rectangle("black_screen", 300.0f, 300.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    //pagina de game over
    Mesh* red_x = create_rectangle("red_x", 0.3f, 6.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    AddMeshToList(brown_mountain1);
    AddMeshToList(brown_mountain2);
    AddMeshToList(brown_mountain3);
    AddMeshToList(paralelipiped_negru);
    AddMeshToList(paralelipiped_verde);
    AddMeshToList(paralelipiped_verde_vagon);
    AddMeshToList(cilindru_albastru);
    AddMeshToList(paralelipiped_galben);
    AddMeshToList(cilindru_rosu);
    AddMeshToList(box_pink);
    AddMeshToList(grass);
    AddMeshToList(water1);
    AddMeshToList(water2);
    AddMeshToList(lake);
    AddMeshToList(mountain1);
    AddMeshToList(mountain2);
    AddMeshToList(station1);
    AddMeshToList(station2);
    AddMeshToList(station2_1);
    AddMeshToList(station2_2);
    AddMeshToList(station2_3);
    AddMeshToList(station2_4);
    AddMeshToList(station2_5);
    AddMeshToList(station2_6);
    AddMeshToList(station2_7);
    AddMeshToList(station2_8);
    AddMeshToList(station2_9);
    AddMeshToList(station2_10);
    AddMeshToList(station2_11);
    AddMeshToList(station3);
    AddMeshToList(station4);
    AddMeshToList(track_vertical);
    AddMeshToList(track_horizontal);
    AddMeshToList(tunnel_navy_horizontal);
    AddMeshToList(tunnel_white_horizontal);
    AddMeshToList(tunnel_navy_vertical);
    AddMeshToList(tunnel_white_vertical);
    AddMeshToList(bridge_navy1);
    AddMeshToList(bridge_white1);
    AddMeshToList(bridge_navy2);
    AddMeshToList(bridge_white2);
    AddMeshToList(zid_negru_v);
    AddMeshToList(zide_negru_h);
    AddMeshToList(black_screen);
    AddMeshToList(red_x);
    AddMeshToList(small_station1);
    AddMeshToList(small_station3);
    AddMeshToList(small_station4);

    //s1, s2, .. s36 reprezinta segmentele de sine care compun rail-uri
    //daca am o linie dreapta care nu e impratita de intersectii formata din sina normala + pod + sina normala
    //atunci o voi reprezenta printr-un rail compus din cele 3 segmente
    s1.end = glm::vec3(-11.0f, 0.02f, -9.4f);
    s1.start = glm::vec3(-11.0f, 0.02f, -5.0f);
    s1.length = glm::length(s1.end - s1.start);

    s2.start = glm::vec3(-10.8f, 0.02f, -5.0f);
    s2.end = glm::vec3(-10.0f, 0.02f, -5.0f);
    s2.length = glm::length(s2.end - s2.start);

    s3_i.start = glm::vec3(-10.0f, 0.02f, -5.0f);
    s3_i.end = glm::vec3(-7.8f, 0.021f, -5.0f);
    s3_i.length = glm::length(s3_i.end - s3_i.start);

    s3_ii.start = glm::vec3(-7.6f, 0.02f, -5.0f);
    s3_ii.end = glm::vec3(-5.6f, 0.021f, -5.0f);
    s3_ii.length = glm::length(s3_ii.end - s3_ii.start);

    s4_i.start = glm::vec3(-5.6f, 0.02f, -5.0f);
    s4_i.end = glm::vec3(-4.6f, 0.02f, -5.0f);
    s4_i.length = glm::length(s4_i.end - s4_i.start);

    s4_ii.start = glm::vec3(-4.4f, 0.02f, -5.0f);
    s4_ii.end = glm::vec3(-3.2f, 0.02f, -5.0f);
    s4_ii.length = glm::length(s4_ii.end - s4_ii.start);

    s5.start = glm::vec3(-3.2f, 0.02f, -5.0f);
    s5.end = glm::vec3(-2.0f, 0.02f, -5.0f);
    s5.length = glm::length(s5.end - s5.start);

    s6.start = glm::vec3(-2.0f, 0.02f, -5.0f);
    s6.end = glm::vec3(-0.4f, 0.02f, -5.0f);
    s6.length = glm::length(s6.end - s6.start);

    s7_i.start = glm::vec3(-4.0f, 0.02f, -4.8f);
    s7_i.end = glm::vec3(-4.0f, 0.02f, 0.0f);
    s7_i.length = glm::length(s7_i.end - s7_i.start);

    s7_ii.start = glm::vec3(-4.0f, 0.02f, 0.4f);
    s7_ii.end = glm::vec3(-4.0f, 0.02f, 1.8f);
    s7_ii.length = glm::length(s7_ii.end - s7_ii.start);

    s8.start = glm::vec3(-3.8f, 0.02f, 2.0f);
    s8.end = glm::vec3(0.2f, 0.02f, 2.0f);
    s8.length = glm::length(s8.end - s8.start);

    s9.start = glm::vec3(0.2f, 0.02f, 2.0f);
    s9.end = glm::vec3(1.6f, 0.02f, 2.0f);
    s9.length = glm::length(s9.end - s9.start);

    s10.start = glm::vec3(1.6f, 0.02f, 2.0f);
    s10.end = glm::vec3(5.4f, 0.02f, 2.0f);
    s10.length = glm::length(s10.end - s10.start);

    s11.start = glm::vec3(5.4f, 0.02f, 2.0f);
    s11.end = glm::vec3(6.2f, 0.02f, 2.0f);
    s11.length = glm::length(s11.end - s11.start);

    s12.start = glm::vec3(10.7f, 0.02f, 0.4f);
    s12.end = glm::vec3(10.7f, 0.02f, -7.45f);
    s12.length = glm::length(s12.end - s12.start);

    s13.start = glm::vec3(10.7f, 0.02f, -7.55f);
    s13.end = glm::vec3(10.7f, 0.02f, -9.05f);
    s13.length = glm::length(s13.end - s13.start);

    s14.start = glm::vec3(-11.2f, 0.02f, -9.8f);
    s14.end = glm::vec3(-12.6f, 0.02f, -9.8f);
    s14.length = glm::length(s14.end - s14.start);

    s15_i.start = glm::vec3(-10.8f, 0.02f, -9.8f);
    s15_i.end = glm::vec3(-8.2f, 0.02f, -9.8f);
    s15_i.length = glm::length(s15_i.end - s15_i.start);

    s15_ii.start = glm::vec3(-8.0f, 0.02f, -9.8f);
    s15_ii.end = glm::vec3(-3.2f, 0.02f, -9.8f);
    s15_ii.length = glm::length(s15_ii.end - s15_ii.start);

    s16.start = glm::vec3(-3.2f, 0.02f, -9.8f);
    s16.end = glm::vec3(-1.8f, 0.02f, -9.8f);
    s16.length = glm::length(s16.end - s16.start);

    s17.start = glm::vec3(-1.8f, 0.02f, -9.8f);
    s17.end = glm::vec3(0.4f, 0.02f, -9.8f);
    s17.length = glm::length(s17.end - s17.start);

    s18.start = glm::vec3(1.0f, 0.02f, -10.0f);
    s18.end = glm::vec3(1.0f, 0.02f, -8.0f);
    s18.length = glm::length(s18.end - s18.start);

    s19.start = glm::vec3(1.2f, 0.02f, -7.6f);
    s19.end = glm::vec3(1.4f, 0.02f, -7.6f);
    s19.length = glm::length(s19.end - s19.start);

    s20.start = glm::vec3(1.8f, 0.02f, -7.4f);
    s20.end = glm::vec3(1.8f, 0.02f, -4.2f);
    s20.length = glm::length(s20.end - s20.start);

    s21.start = glm::vec3(1.8f, 0.02f, -4.2f);
    s21.end = glm::vec3(1.8f, 0.02f, -0.4f);
    s21.length = glm::length(s21.end - s21.start);

    s22.start = glm::vec3(1.8f, 0.02f, -0.4f);
    s22.end = glm::vec3(1.8f, 0.02f, 0.4f);
    s22.length = glm::length(s22.end - s22.start);

    s23.start = glm::vec3(0.8f, 0.02f, -7.6f);
    s23.end = glm::vec3(0.6f, 0.02f, -7.6f);
    s23.length = glm::length(s23.end - s23.start);

    s24_i.start = glm::vec3(0.1f, 0.02f, -7.4f);
    s24_i.end = glm::vec3(0.1f, 0.02f, -5.4f);
    s24_i.length = glm::length(s24_i.end - s24_i.start);

    s24_ii.start = glm::vec3(0.1f, 0.02f, -5.4f);
    s24_ii.end = glm::vec3(0.1f, 0.02f, -4.2f);
    s24_ii.length = glm::length(s24_ii.end - s24_ii.start);

    s25.start = glm::vec3(0.1f, 0.02f, -4.2f);
    s25.end = glm::vec3(0.1f, 0.02f, -0.4f);
    s25.length = glm::length(s25.end - s25.start);

    s26.start = glm::vec3(0.1f, 0.02f, -0.4f);
    s26.end = glm::vec3(0.1f, 0.02f, 0.4f);
    s26.length = glm::length(s26.end - s26.start);

    s27.start = glm::vec3(1.0f, 0.02f, -10.0f);
    s27.end = glm::vec3(1.0f, 0.02f, -12.4f);
    s27.length = glm::length(s27.end - s27.start);

    s28.start = glm::vec3(-7.6f, 0.02f, -9.6f);
    s28.end = glm::vec3(-7.6f, 0.02f, -8.8f);
    s28.length = glm::length(s28.end - s28.start);

    s29.start = glm::vec3(-12.8f, 0.02f, -9.6f);
    s29.end = glm::vec3(-12.8f, 0.02f, 0.0f);
    s29.length = glm::length(s29.end - s29.start);

    s30_i.start = glm::vec3(-12.6f, 0.02f, 0.4f);
    s30_i.end = glm::vec3(-8.0f, 0.02f, 0.4f);
    s30_i.length = glm::length(s30_i.end - s30_i.start);

    s30_ii.start = glm::vec3(-7.8f, 0.02f, 0.4f);
    s30_ii.end = glm::vec3(-4.6f, 0.02f, 0.4f);
    s30_ii.length = glm::length(s30_ii.end - s30_ii.start);

    s30_iii.start = glm::vec3(-4.4f, 0.02f, 0.4f);
    s30_iii.end = glm::vec3(-0.2f, 0.02f, 0.4f);
    s30_iii.length = glm::length(s30_iii.end - s30_iii.start);

    s30_iv.start = glm::vec3(0.0f, 0.02f, 0.4f);
    s30_iv.end = glm::vec3(0.2f, 0.02f, 0.4f);
    s30_iv.length = glm::length(s30_iv.end - s30_iv.start);

    s31.start = glm::vec3(0.2f, 0.02f, 0.4f);
    s31.end = glm::vec3(1.6f, 0.02f, 0.4f);
    s31.length = glm::length(s31.end - s31.start);

    s32_i.start = glm::vec3(1.6f, 0.02f, 0.4f);
    s32_i.end = glm::vec3(1.8f, 0.02f, 0.4f);
    s32_i.length = glm::length(s32_i.end - s32_i.start);

    s32_ii.start = glm::vec3(1.8f, 0.02f, 0.4f);
    s32_ii.end = glm::vec3(5.4f, 0.02f, 0.4f);
    s32_ii.length = glm::length(s32_ii.end - s32_ii.start);

    s33.start = glm::vec3(5.4f, 0.02f, 0.4f);
    s33.end = glm::vec3(9.9f, 0.02f, 0.4f);
    s33.length = glm::length(s33.end - s33.start);

    s34.start = glm::vec3(9.9f, 0.02f, 0.4f);
    s34.end = glm::vec3(10.7f, 0.02f, 0.4f);
    s34.length = glm::length(s34.end - s34.start);

    s35.start = glm::vec3(-7.6f, 0.02f, -2.0f);
    s35.end = glm::vec3(-7.6f, 0.02f, 0.2f);
    s35.length = glm::length(s35.end - s35.start);

    s36_i.start = glm::vec3(-7.6f, 0.02f, -5.2f);
    s36_i.end = glm::vec3(-7.6f, 0.02f, -2.0f);
    s36_i.length = glm::length(s36_i.end - s36_i.start);

    s36_ii.start = glm::vec3(-7.6f, 0.02f, -8.8f);
    s36_ii.end = glm::vec3(-7.6f, 0.02f, -5.2f);
    s36_ii.length = glm::length(s36_ii.end - s36_ii.start);

	//intersectiile sunt locurile unde trenul se opreste si asteapta comenzi de la jucator pentru a alege urmatorul rail pe care sa mearga
    I1 = new Intersection();
    I2 = new Intersection();
    I3 = new Intersection();
    I4 = new Intersection();
    I5 = new Intersection();
    I6 = new Intersection();
    I7 = new Intersection();
    I8 = new Intersection();
    I9 = new Intersection();
    I10 = new Intersection();
    I11 = new Intersection();
    Donut = new Intersection();
    Box = new Intersection();
    Pyramid = new Intersection();
    Sphere = new Intersection();
	jos_spre_donut = new Intersection();
    spre_piramida = new Intersection();
	stanga_sus = new Intersection();
	stanga_jos = new Intersection();
	lac_stanga = new Intersection();
	lac_dreapta = new Intersection();

    //aici in rail pastrez segmentele din care sunt compuse si intersectiile pe care le leaga
    rail_A = new Rail();
    rail_A->segments = { s14 };
    rail_A->length = s14.length;
    rail_A->inters_A = I1;
    rail_A->inters_B = stanga_sus;
    rails.push_back(rail_A);

    rail_A1 = new Rail();
    rail_A1->segments = { s29 };
    rail_A1->length = s29.length;
    rail_A1->inters_A = stanga_sus;
    rail_A1->inters_B = stanga_jos;
    rails.push_back(rail_A1);

    rail_A2 = new Rail();
    rail_A2->segments = { s30_i };
    rail_A2->length = s30_i.length;
    rail_A2->inters_A = stanga_jos;
    rail_A2->inters_B = I4;
    rails.push_back(rail_A2);

    rail_B = new Rail();
    rail_B->segments = { s1 };
    rail_B->length = s1.length;
    rail_B->inters_A = I1;
    rail_B->inters_B = Sphere;
    rails.push_back(rail_B);

    rail_B2 = new Rail();
    rail_B2->segments = { s2, s3_i };
    rail_B2->length = s2.length + s3_i.length;
    rail_B2->inters_A = Sphere;
    rail_B2->inters_B = I3;
    rails.push_back(rail_B2);

    rail_C = new Rail();
    rail_C->segments = { s15_i };
    rail_C->length = s15_i.length;
    rail_C->inters_A = I1;
    rail_C->inters_B = I2;
    rails.push_back(rail_C);

    rail_D = new Rail();
    rail_D->segments = { s28, s36_ii };
    rail_D->length = s28.length + s36_ii.length;
    rail_D->inters_A = I2;
    rail_D->inters_B = I3;
    rails.push_back(rail_D);

    rail_E = new Rail();
    rail_E->segments = { s3_ii, s4_i };
    rail_E->length = s3_ii.length + s4_i.length;
    rail_E->inters_A = I3;
    rail_E->inters_B = I5;
    rails.push_back(rail_E);

    rail_F = new Rail();
    rail_F->segments = { s36_i, s35 };
    rail_F->length = s35.length + s36_i.length;
    rail_F->inters_A = I3;
    rail_F->inters_B = I4;
    rails.push_back(rail_F);

    rail_G = new Rail();
    rail_G->segments = { s30_ii };
    rail_G->length = s30_ii.length;
    rail_G->inters_A = I4;
    rail_G->inters_B = I6;
    rails.push_back(rail_G);

    rail_H = new Rail();
    rail_H->segments = { s7_i };
    rail_H->length = s7_i.length;
    rail_H->inters_A = I5;
    rail_H->inters_B = I6;
    rails.push_back(rail_H);

    rail_I = new Rail();
    rail_I->segments = { s15_ii, s16, s17 };
    rail_I->length = s15_ii.length + s16.length + s17.length;
    rail_I->inters_A = I2;
    rail_I->inters_B = I8;
    rails.push_back(rail_I);

    rail_J = new Rail();
    rail_J->segments = { s4_ii, s5, s6 };
    rail_J->length = s4_ii.length + s5.length + s6.length;
    rail_J->inters_A = I5;
    rail_J->inters_B = I7;
    rails.push_back(rail_J);

    rail_K = new Rail();
    rail_K->segments = { s30_iii };
    rail_K->length = s30_iii.length;
    rail_K->inters_A = I6;
    rail_K->inters_B = I10;
    rails.push_back(rail_K);

    rail_L = new Rail();
    rail_L->segments = { s7_ii };
    rail_L->length = s7_ii.length;
    rail_L->inters_A = I6;
    rail_L->inters_B = jos_spre_donut;
    rails.push_back(rail_L);

    rail_L2 = new Rail();
    rail_L2->segments = { s8, s9, s10, s11 };
    rail_L2->length = s8.length + s9.length + s10.length + s11.length;
    rail_L2->inters_A = jos_spre_donut;
    rail_L2->inters_B = Donut;
    rails.push_back(rail_L2);

    rail_M = new Rail();
    rail_M->segments = { s27 };
    rail_M->length = s27.length;
    rail_M->inters_A = I8;
    rail_M->inters_B = Box;
    rails.push_back(rail_M);

    rail_N = new Rail();
    rail_N->segments = { s18 };
    rail_N->length = s18.length;
    rail_N->inters_A = I8;
    rail_N->inters_B = I9;
    rails.push_back(rail_N);

    rail_O = new Rail();
    rail_O->segments = { s23 };
    rail_O->length = s23.length;
    rail_O->inters_A = I9;
    rail_O->inters_B = lac_stanga;
    rails.push_back(rail_O);

    rail_O1 = new Rail();
    rail_O1->segments = { s24_i };
    rail_O1->length = s24_i.length;
    rail_O1->inters_A = lac_stanga;
    rail_O1->inters_B = I7;
    rails.push_back(rail_O1);

    rail_P = new Rail();
    rail_P->segments = { s19 };
    rail_P->length = s19.length;
    rail_P->inters_A = I9;
    rail_P->inters_B = lac_dreapta;
    rails.push_back(rail_P);

    rail_P1 = new Rail();
    rail_P1->segments = { s20, s21, s22 };
    rail_P1->length = s20.length + s21.length + s22.length;
    rail_P1->inters_A = lac_dreapta;
    rail_P1->inters_B = I11;
    rails.push_back(rail_P1);

    rail_Q = new Rail();
    rail_Q->segments = { s24_ii, s25, s26 };
    rail_Q->length = s24_ii.length + s25.length + s26.length;
    rail_Q->inters_A = I7;
    rail_Q->inters_B = I10;
    rails.push_back(rail_Q);

    rail_R = new Rail();
    rail_R->segments = { s30_iv, s31, s32_i };
    rail_R->length = s30_iv.length + s31.length + s32_i.length;
    rail_R->inters_A = I10;
    rail_R->inters_B = I11;
    rails.push_back(rail_R);

    rail_S = new Rail();
    rail_S->segments = { s32_ii, s33, s34 };
    rail_S->length = s32_ii.length + s33.length + s34.length;
    rail_S->inters_A = I11;
    rail_S->inters_B = spre_piramida;
    rails.push_back(rail_S);

    rail_S2 = new Rail();
    rail_S2->segments = { s12, s13 };
    rail_S2->length = s12.length + s13.length;
    rail_S2->inters_A = spre_piramida;
    rail_S2->inters_B = Pyramid;
    rails.push_back(rail_S2);

	//in intersectii trebuie retinut pozitia sa (coordonata) si rail-urile in care se poate merge de acolo
    I1->position = s1.end;
    I1->connected_rails = { rail_A, rail_B, rail_C };

    I2->position = s15_i.end;
    I2->connected_rails = { rail_C, rail_D, rail_I };

    I3->position = s3_i.end;
    I3->connected_rails = { rail_B2, rail_D, rail_F, rail_E };

    I4->position = s30_i.end;
    I4->connected_rails = { rail_A2, rail_F, rail_G };

    I5->position = s4_i.end;
    I5->connected_rails = { rail_E, rail_H, rail_J };

    I6->position = s30_ii.end;
    I6->connected_rails = { rail_G, rail_H, rail_L, rail_K };

    I7->position = s6.end;
    I7->connected_rails = { rail_J, rail_O1, rail_Q };

    I8->position = s27.start;
    I8->connected_rails = { rail_I, rail_M, rail_N };

    I9->position = s19.start;
    I9->connected_rails = { rail_N, rail_O, rail_P };

    I10->position = s30_iii.end;
    I10->connected_rails = { rail_K, rail_Q, rail_R };

    I11->position = s32_i.end;
    I11->connected_rails = { rail_P1, rail_R, rail_S };

    Donut->position = s11.end;
    Donut->connected_rails = { rail_L };
    Donut->is_terminal = true;

    Box->position = s27.end;
    Box->connected_rails = { rail_M };
    Box->is_terminal = true;

    Pyramid->position = s13.end;
    Pyramid->connected_rails = { rail_S };
    Pyramid->is_terminal = true;

    Sphere->position = s1.end;
    Sphere->connected_rails = { rail_B, rail_B2 };

	jos_spre_donut->position = s8.start;
	jos_spre_donut->connected_rails = { rail_L, rail_L2 };

	spre_piramida->position = s12.start;
	spre_piramida->connected_rails = { rail_S, rail_S2 };

	stanga_sus->position = s14.end;
	stanga_sus->connected_rails = { rail_A, rail_A1 };

	stanga_jos->position = s30_i.start;
	stanga_jos->connected_rails = { rail_A1, rail_A2 };

	lac_stanga->position = s23.start;
	lac_stanga->connected_rails = { rail_O, rail_O1 };

	lac_dreapta->position = s19.start;
	lac_dreapta->connected_rails = { rail_P, rail_P1 };

	//pozitia initiala a trenului
    train_pos = glm::vec3(-8.0f, 0.05f, -5.0f);
    train.rail = rail_B2;
    train.from = rail_B2->inters_A;
    train.to = rail_B2->inters_B;
    train.dist = 0.0f;
    train.stopped = false;
    train.dir = DIR_RIGHT;
    train.waiting_At_intersection = false;

}

void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

//practic functia determina pe ce segment se afla trenul
glm::vec3 GetPositionOnRail(Rail* rail, float dist)
{
    float remaining = dist;

	//ia fiecare segment al rail-ului si verifica daca distanta ramasa e mai mica decat lungimea segmentului
    for (auto& seg : rail->segments) {

        if (remaining <= seg.length) {
            float t = remaining / seg.length;
            return seg.start + t * (seg.end - seg.start);
        }
        remaining -= seg.length;
    }

    return rail->segments.back().end;
}

//orientez trenul in functie de tipul de rail pe care se afla
float GetTrainRotation(Rail* rail, bool forward)
{
    glm::vec3 dir;

    if (forward) {
        dir = rail->segments.back().end - rail->segments.front().start;
    }
    else {
        dir = rail->segments.front().start - rail->segments.back().end;
    }

    dir = glm::normalize(dir);
    return atan2(dir.z, dir.x);
}

// ultimul arg mai mic == mai sus pe desen
// primularg mai mare = mai la dreapta pe desen
void Tema2::Update(float deltaTimeSeconds)
{
    //timer de 60 de sec. dupa 1 minut apare ecranul de game over
    timer_total += deltaTimeSeconds;

    if (!black_screen)
    {
        current_sphere = (int)(timer_total / 5.0f);
        if (current_sphere >= 12) {
            float timeAfterLast = timer_total - 12 * 5.0f;

            if (timeAfterLast >= 1.0f) {
                black_screen = true;
            }
            else {
                current_sphere = 11;
            }
        }
    }

    //viteza constanta a trenului
    float speed = 5.0f;

    if (!train.stopped) {

        if (train.forward)
            train.dist += speed * deltaTimeSeconds;
        else
            train.dist -= speed * deltaTimeSeconds;

        if (train.dist <= 0.0f || train.dist >= train.rail->length) {
            train.dist = glm::clamp(train.dist, 0.0f, train.rail->length);
            train.stopped = true;
            train.waiting_At_intersection = true;
        }
    }

    train_pos = GetPositionOnRail(train.rail, train.dist);
    train_pos.y = 0.05f;
    float trainAngle = GetTrainRotation(train.rail, train.forward);


    glm::mat4 modelMatrix = glm::mat4(1);
    RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-16, 0.05f, -9.0f));
    RenderMesh(meshes["zid_negru_v"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(14, 0.05f, -9.0f));
    RenderMesh(meshes["zid_negru_v"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0, 0.05f, 6.0f));
    RenderMesh(meshes["zid_negru_h"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.05f, -24.0f));
    RenderMesh(meshes["zid_negru_h"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 0.01f, 4.5));
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 0.01f, -17.5));
    RenderMesh(meshes["brown_mountain1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 0.01f, -14.5));
    RenderMesh(meshes["brown_mountain2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-8, 0.01f, -17.0f));
    RenderMesh(meshes["brown_mountain3"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8, 0.01f, -17.5));
    RenderMesh(meshes["brown_mountain1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.01f, -19));
    RenderMesh(meshes["brown_mountain2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0.01f, -15.5));
    RenderMesh(meshes["brown_mountain2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.5, 0.01f, -15.0));
    RenderMesh(meshes["brown_mountain2"], shaders["VertexColor"], modelMatrix);
    //plansa
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 0.01f, 4.5));
    RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.25, 0.01f, 3.5));
    RenderMesh(meshes["water2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25, 0.01f, 3.5));
    RenderMesh(meshes["water2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.01f, 2.75));
    RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.01f, 0.75));
    RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.95f, 0.01f, -2.15));
    RenderMesh(meshes["lake"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(11.0f, 0.01f, -10.0));
    RenderMesh(meshes["lake"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.6, 0.01f, -1.25f));
    RenderMesh(meshes["water2"], shaders["VertexColor"], modelMatrix);
    for (int i = 0; i < 12; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.01f, -2.0f - i * 2));
        RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.5, 0.01f, -1.25f));
    RenderMesh(meshes["water2"], shaders["VertexColor"], modelMatrix);
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4.4f, 0.01f, -2.0f - i * 2));
        RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(5.15, 0.01f, -7.0f));
    RenderMesh(meshes["water2"], shaders["VertexColor"], modelMatrix);
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(6.05f, 0.01f, -7.75f - i * 2));
        RenderMesh(meshes["water1"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.5f, 0.01f, -5.0f));
    RenderMesh(meshes["mountain1"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7.0f, 0.01f, 2.0f));
    RenderMesh(meshes["mountain2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(8.0f, 0.01f, 0));
    RenderMesh(meshes["mountain2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(9.0f, 0.01f, -2.0f));
    RenderMesh(meshes["mountain2"], shaders["VertexColor"], modelMatrix);
    //garile
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0.65f, -13));
    RenderMesh(meshes["box"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(11, 0.1f, -10));
    RenderMesh(meshes["pyramid"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7.0f, 0.2f, 2.0f));
    RenderMesh(meshes["torus"], shaders["VertexColor"], modelMatrix);
    //gara centrala
    if (!black_screen)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 0.5f, -4.5));

        std::string sphereName = "sphere_" + std::to_string(current_sphere);
        RenderMesh(meshes[sphereName], shaders["VertexColor"], modelMatrix);
    }
    //trenul efectiv:
    //vagon
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5f, 0.49f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
    RenderMesh(meshes["paralelipiped_verde_vagon"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5f, 0.19f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
    RenderMesh(meshes["paralelipiped_galben"], shaders["VertexColor"], modelMatrix);
    float dist = 0.17f;
    for (int i = 0; i < 7; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, train_pos);
        modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.05 + i * dist, 0.05f, -0.2f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
        RenderMesh(meshes["cilindru_rosu"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < 7; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, train_pos);
        modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.05 + i * dist, 0.05f, 0.2f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
        RenderMesh(meshes["cilindru_rosu"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.75f, 0.25f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
    RenderMesh(meshes["paralelipiped_negru"], shaders["VertexColor"], modelMatrix);
    //locomotiva
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.35f, 0.49f, 0.0f));
    RenderMesh(meshes["paralelipiped_verde"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.15f, 0.39f, 0.0f));
    RenderMesh(meshes["cilindru_albastru"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.19f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
    RenderMesh(meshes["paralelipiped_galben"], shaders["VertexColor"], modelMatrix);
    for (int i = 0; i < 7; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, train_pos);
        modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.55 + i * dist, 0.05f, -0.2f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
        RenderMesh(meshes["cilindru_rosu"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < 7; i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, train_pos);
        modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.55 + i * dist, 0.05f, 0.2f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
        RenderMesh(meshes["cilindru_rosu"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, train_pos);
    modelMatrix = glm::rotate(modelMatrix, trainAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.51f, 0.39f, 0.0f));
    RenderMesh(meshes["box_pink"], shaders["VertexColor"], modelMatrix);

    // [1] din sfera in sus
    for (int i = 0; i < 12; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.0f, 0.02f, -5.0f - i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    // [2] din sfera in dreapta
    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.8f + i * 0.2f, 0.02f, -5.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[3.i] in muntele 1 din sfera spre dreapta folosind PODUL
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.2f + i * 0.2f, 0.021f, -4.85f - (j * 0.16f + 0.08)));
            RenderMesh(meshes["bridge_navy1"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.2f + i * 0.2f, 0.021f, -4.85f - k * 0.16f));
            RenderMesh(meshes["bridge_white1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[3.ii]
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.2f + i * 0.2f, 0.021f, -4.85f - (j * 0.16f + 0.08)));
            RenderMesh(meshes["bridge_navy1"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.2f + i * 0.2f, 0.021f, -4.85f - k * 0.16f));
            RenderMesh(meshes["bridge_white1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[4.i] tot spre dreapta din muntele 1 dupa pod
    for (int i = 0; i < 6; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.6f + i * 0.2f, 0.02f, -5.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[4.ii]
    for (int i = 0; i < 7; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.4f + i * 0.2f, 0.02f, -5.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[5] trec raul de dupa muntele 1
    {
        for (int i = 0; i < 4; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.2f - i * 0.2f, 0.03f, -5.0f));
            RenderMesh(meshes["tunnel_navy_horizontal"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.3f - i * 0.2f, 0.03f, -5.0f));
            RenderMesh(meshes["tunnel_white_horizontal"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[6] continui in dreapta 
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.0f + i * 0.2f, 0.02f, -5.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[7.i] in jos mai creez o intersectie care merge spre gara 4
    for (int i = 0; i < 13; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 0.02f, -4.8f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[7.ii]
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.0f, 0.02f, 0.4f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[8] in dreapta spre gara Donut
    for (int i = 0; i < 21; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.8f + i * 0.2f, 0.02f, 2.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[9] aici trec lacul spre gara Donut
    {
        for (int i = 0; i < 4; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.25f - i * 0.2f, 0.02f, 2.0f));
            RenderMesh(meshes["tunnel_navy_horizontal"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.15f - i * 0.2f, 0.02f, 2.0f));
            RenderMesh(meshes["tunnel_white_horizontal"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[10] aici ajung la Donut direct
    for (int i = 0; i < 20; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.6f + i * 0.2f, 0.02f, 2.0f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[11]
    {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(6.2f, 0.021f, 2.15f - (j * 0.16f + 0.08)));
            RenderMesh(meshes["bridge_navy1"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(6.2f, 0.021f, 2.15f - k * 0.16f));
            RenderMesh(meshes["bridge_white1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[12] sina lunga spre piramida
    for (int i = 0; i < 20; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(11.0f, 0.02f, -7.45f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[13] trec lacul spre piramida
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(11.0f, 0.05f, (-9.05f - j * 0.21f) + i * 0.4f));
            RenderMesh(meshes["tunnel_navy_vertical"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(11.0f, 0.05f, (-9.15f - k * 0.21f) + i * 0.4f));
            RenderMesh(meshes["tunnel_white_vertical"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[14] deasupra sferei spre stanga
    for (int i = 0; i < 8; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.2 - i * 0.2f, 0.02f, -9.8f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[15 STANGA] deasupra sferei spre dreapta
    for (int i = 0; i < 14; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.8 + i * 0.2f, 0.02f, -9.8f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[15 DREAPTA]
    for (int i = 0; i < 25; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.0 + i * 0.2f, 0.02f, -9.8f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[16] trec rau in partea stanga spre gara centrala
    {
        for (int i = 0; i < 4; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.2f - i * 0.2f, 0.02f, -9.8f));
            RenderMesh(meshes["tunnel_navy_horizontal"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.3f - i * 0.2f, 0.02f, -9.8f));
            RenderMesh(meshes["tunnel_white_horizontal"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[17] dupa ce trec raul tot in dreapta spre gara centrala
    for (int i = 0; i < 12; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.8f + i * 0.2f, 0.02f, -9.8f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[18] intersectia garii in jos 
    for (int i = 0; i < 6; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.02f, -10.0f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[19] in dreapta -- despart ramura spre dreapta care trece prin lac
    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.2f + i * 0.2f, 0.02f, -7.6f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[20] trece prin lac in partea dreapta
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f, 0.03f, -7.4f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[21] trece lacul in partea dreapta
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f, 0.03f, (-0.4f - j * 0.2f) - i * 0.4f));
            RenderMesh(meshes["tunnel_navy_vertical"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f, 0.03f, (-0.5f - k * 0.2f) - i * 0.4f));
            RenderMesh(meshes["tunnel_white_vertical"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[22] dupa ce a trecut lacul in partea dreapta merg in continuare in jos
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f, 0.03f, 0.0f));
    RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);

    //[23] ramura spre stanga care va trece prin lac
    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.8f - i * 0.2f, 0.02f, -7.6f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[24.i] trece prin lac in partea stanga
    for (int i = 0; i < 6; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, 0.03f, -5.4f - i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[24.ii]
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, 0.03f, -4.2f - i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[25] 
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, 0.03f, (-0.4f - j * 0.2f) - i * 0.4f));
            RenderMesh(meshes["tunnel_navy_vertical"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, 0.03f, (-0.5f - k * 0.2f) - i * 0.4f));
            RenderMesh(meshes["tunnel_white_vertical"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[26]
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, 0.03f, 0.0f));
    RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);

    //[27] in sus spre gara centrala
    for (int i = 0; i < 7; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.02f, -10.0f - i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);

    }

    //[28] in jos deasupra muntelui 1 
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.6f, 0.02f, -9.6f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[29] in jos din stanga sferei
    for (int i = 0; i < 25; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-12.8f, 0.02f, -9.6f + i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[30.i] in dreapta odata ajuns jos de tot din stanga sferei -- 65
    for (int i = 0; i < 24; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-12.6 + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[30.ii]
    for (int i = 0; i < 17; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.8 + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[30.iii]
    for (int i = 0; i < 22; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.4 + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[30.iv]
    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0 + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[31] trec raul in partea de jos a lacului
    {
        for (int i = 0; i < 4; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.2f - i * 0.2f, 0.02f, 0.4f));
            RenderMesh(meshes["tunnel_navy_horizontal"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.1f - i * 0.2f, 0.02f, 0.4f));
            RenderMesh(meshes["tunnel_white_horizontal"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[32.i] continui in dreapta inspre muntele 2
    for (int i = 0; i < 1; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.6f + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[32.ii]
    for (int i = 0; i < 19; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.8f + i * 0.2f, 0.02f, 0.4f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[33] trec muntele 2 tot inspre dreapta
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(5.9f + i * 0.2f, 0.021f, 0.5f - (j * 0.16f + 0.08)));
            RenderMesh(meshes["bridge_navy1"], shaders["VertexColor"], modelMatrix);
        }

        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(5.9f + i * 0.2f, 0.021f, 0.5f - k * 0.16f));
            RenderMesh(meshes["bridge_white1"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[34] 
    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(9.9f + i * 0.2f, 0.02f, 0.35f));
        RenderMesh(meshes["track_horizontal"], shaders["VertexColor"], modelMatrix);
    }

    //[35] in sus spre muntele 1
    for (int i = 0; i < 5; i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.6f, 0.02f, 0.2f - i * 0.4f));
        RenderMesh(meshes["track_vertical"], shaders["VertexColor"], modelMatrix);
    }

    //[36.i] in sus pe muntele 1 folosind PODUL
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.7f + (j * 0.16f + 0.08), 0.03f, -2.0f - i * 0.4f));
            RenderMesh(meshes["bridge_navy2"], shaders["VertexColor"], modelMatrix);
        }
        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.7f + k * 0.16f, 0.03f, -2.0f - i * 0.4f));
            RenderMesh(meshes["bridge_white2"], shaders["VertexColor"], modelMatrix);
        }
    }

    //[36.ii]
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.7f + (j * 0.16f + 0.08), 0.03f, -5.2f - i * 0.4f));
            RenderMesh(meshes["bridge_navy2"], shaders["VertexColor"], modelMatrix);
        }
        for (int k = 0; k < 3; k++) {
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.7f + k * 0.16f, 0.03f, -5.2f - i * 0.4f));
            RenderMesh(meshes["bridge_white2"], shaders["VertexColor"], modelMatrix);
        }
    }

    //jocul efectiv
    //0 = box, 1 = piramida, 2 = torus

    //generez o comanda de resurse random
    //evit sa am 2 resurse de acelasi tip consecutive pentru a face nivelul mai dificil si a supune jucatorul sa faca mai multe miscari
    if (generate_command == 0) {
        generate_command = 1;
        for (int i = 0; i < 5; i++) {
            v[i] = rand() % 3;
            if (i >= 1) {
                while (v[i] == v[i - 1]) {
                    v[i] = rand() % 3;
                }
            }
        }
        command1 = v[0];
        command2 = v[1];
        command3 = v[2];
        command4 = v[3];
        command5 = v[4];
    }

    //aceste coordonate reprezinta coordonatele garilor de resurse
    if (command1 == 0) {
        c1x = 1.00f;
        c1y = 0.05f;
        c1z = -12.4f;
    }
    else if (command1 == 1) {
        c1x = 10.7f;
        c1y = 0.05f;
        c1z = -9.049999f;
    }
    else if (command1 == 2) {
        c1x = 6.2f;
        c1y = 0.05f;
        c1z = 2.00f;
    }

    if (command2 == 0) {
        c2x = 1.00f;
        c2y = 0.05f;
        c2z = -12.4f;
    }
    else if (command2 == 1) {
        c2x = 10.7f;
        c2y = 0.05f;
        c2z = -9.049999f;
    }
    else if (command2 == 2) {
        c2x = 6.2f;
        c2y = 0.05f;
        c2z = 2.00f;
    }

    if (command3 == 0) {
        c3x = 1.00f;
        c3y = 0.05f;
        c3z = -12.4f;
    }
    else if (command3 == 1) {
        c3x = 10.7f;
        c3y = 0.05f;
        c3z = -9.049999f;
    }
    else if (command3 == 2) {
        c3x = 6.2f;
        c3y = 0.05f;
        c3z = 2.00f;
    }

    if (command4 == 0) {
        c4x = 1.00f;
        c4y = 0.05f;
        c4z = -12.4f;
    }
    else if (command4 == 1) {
        c4x = 10.7f;
        c4y = 0.05f;
        c4z = -9.049999f;
    }
    else if (command4 == 2) {
        c4x = 6.2f;
        c4y = 0.05f;
        c4z = 2.00f;
    }

    if (command5 == 0) {
        c5x = 1.00f;
        c5y = 0.05f;
        c5z = -12.4f;
    }
    else if (command5 == 1) {
        c5x = 10.7f;
        c5y = 0.05f;
        c5z = -9.049999f;
    }
    else if (command5 == 2) {
        c5x = 6.2f;
        c5y = 0.05f;
        c5z = 2.00f;
    }

    command_now[0] = glm::vec3(c1x, c1y, c1z);
    command_now[1] = glm::vec3(c2x, c2y, c2z);
    command_now[2] = glm::vec3(c3x, c3y, c3z);
    command_now[3] = glm::vec3(c4x, c4y, c4z);
    command_now[4] = glm::vec3(c5x, c5y, c5z);

    //implementare bonus : comenzile sa se ia in ordinea in care sunt facute
    if (current_command < 5)
    {
        glm::vec3 target = command_now[current_command];

        if (glm::distance(train_pos, target) < 0.6f)
        {
            if (current_command == 0)
                command1_done = true;
            if (current_command == 1) 
                command2_done = true;
            if (current_command == 2) 
                command3_done = true;
            if (current_command == 3) 
                command4_done = true;
            if (current_command == 4) 
                command5_done = true;
            current_command++;
        }
    }

    //dupa ce cele 5 resurse au fost colectate in mai putin de 1 minut, o noua comanda apare pe ecran si se trece la nivelul urmator
    if (command1_done == 1 && command2_done == 1 && command3_done == 1 && command4_done == 1 && command5_done == 1) {
        if (glm::distance(train_pos, glm::vec3(-10.8f, 0.05f, -5.00f)) < 0.6f) {
            generate_command = 0;
            current_command = 0;
            command1_done = 0;
            command2_done = 0;
            command3_done = 0;
            command4_done = 0;
            command5_done = 0;
            timer_total = 0.0f;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 0.5f, -4.5));
            RenderMesh(meshes["sphere_0"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (command1_done == 0) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-12.0f, 0.1f, 3.3f));
        if (v[0] == 0) {
            RenderMesh(meshes["small_box"], shaders["VertexColor"], modelMatrix);
        }
        else if (v[0] == 1) {
            RenderMesh(meshes["small_pyramid"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh(meshes["small_torus"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (command2_done == 0) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.0f, 0.1f, 3.3f));
        if (v[1] == 0) {
            RenderMesh(meshes["small_box"], shaders["VertexColor"], modelMatrix);
        }
        else if (v[1] == 1) {
            RenderMesh(meshes["small_pyramid"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh(meshes["small_torus"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (command3_done == 0) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.0f, 0.1f, 3.3f));
        if (v[2] == 0) {
            RenderMesh(meshes["small_box"], shaders["VertexColor"], modelMatrix);
        }
        else if (v[2] == 1) {
            RenderMesh(meshes["small_pyramid"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh(meshes["small_torus"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (command4_done == 0) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-9.0f, 0.1f, 3.3f));
        if (v[3] == 0) {
            RenderMesh(meshes["small_box"], shaders["VertexColor"], modelMatrix);
        }
        else if (v[3] == 1) {
            RenderMesh(meshes["small_pyramid"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh(meshes["small_torus"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (command5_done == 0) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.0f, 0.1f, 3.3f));
        if (v[4] == 0) {
            RenderMesh(meshes["small_box"], shaders["VertexColor"], modelMatrix);
        }
        else if (v[4] == 1) {
            RenderMesh(meshes["small_pyramid"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh(meshes["small_torus"], shaders["VertexColor"], modelMatrix);
        }
    }


    if (black_screen) {

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 6.0f, 0.0f));
        RenderMesh(meshes["black_screen"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 6.2f, 1.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["red_x"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 6.2f, 1.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-45.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["red_x"], shaders["VertexColor"], modelMatrix);

        endscreen += deltaTimeSeconds;
        if (endscreen > 3.0f) {
            window->Close();
        }
    }


}

void Tema2::FrameEnd()
{
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE,
        glm::value_ptr(camera->GetViewMatrix()));

    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE,
        glm::value_ptr(projectionMatrix));

    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE,
        glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        return;
}

void Tema2::OnKeyPress(int key, int mods)
{

    //daca e apasat click dreapta nu am voie misc trenul
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        return;

    //doar in intersectii are loc schimbarea folosind wasd
    if (!train.waiting_At_intersection)
        return;

    //interesectia in care ma aflu
    Intersection* I = train.to;

    glm::vec3 wanted(0, 0 , 0);

    //aproximare a directiei in care merg - A = la stanga, S = in jos, D = la dreapta, W = in sus
    if (key == GLFW_KEY_A) 
        wanted = glm::vec3(-1, 0, 0);
    if (key == GLFW_KEY_D) 
        wanted = glm::vec3(1, 0, 0);
    if (key == GLFW_KEY_W) 
        wanted = glm::vec3(0, 0, -1);
    if (key == GLFW_KEY_S) 
        wanted = glm::vec3(0, 0, 1);
    if (wanted == glm::vec3(0, 0 ,0))
        return;

    Rail* chosen = nullptr;
    Intersection* next = nullptr;
    float best = 0.5f;

    //trec prin toaten Rails care sunt conectate la intersectia mea
    for (Rail* r : I->connected_rails)
    {

        //capatul unde trebuie sa ajung
        Intersection* other;
        if (r->inters_A == I) {
            other = r->inters_B;
        }
        else {
            other = r->inters_A;
        }

        //primul segment al sinei. de aici pleaca trenul
        Segment& first_seg = r->segments.front();
        glm::vec3 seg;

        //aici verific daca trenul pleaca din pozitia de end a rail-ului sau din pozitia de start
        if (glm::distance(first_seg.start, I->position) < glm::distance(first_seg.end, I->position)) {
            seg = first_seg.end - first_seg.start;
        }
        else {
            seg = first_seg.start - first_seg.end;
        }

        seg = glm::normalize(seg);
        float dot = glm::dot(seg, wanted);

        //retin ca cea mai buna sina
        if (dot > best) {
            best = dot;
            chosen = r;
            next = other;
        }
    }

    //implementarea folosind aproximarea la unele sine nu da efectul dorit asa ca fortez trenul aici chiar sa ia traiectoriile pe care mi le doresc
    if (I == I1 && key == GLFW_KEY_S) {
        chosen = rail_B;
        next = Sphere;
    }
    if (I == I11 && key == GLFW_KEY_W) {
        chosen = rail_P1;
        next = lac_dreapta;
    }
    if (I == I11 && key == GLFW_KEY_A) {
        chosen = rail_R;
        next = I10;
    }
    if (I == I7 && key == GLFW_KEY_W) {
        chosen = rail_O1;
        next = lac_stanga;
    }
    if (I == Pyramid && key == GLFW_KEY_S) {
        chosen = rail_S2;
        next = spre_piramida;
    }
    if (I == I6 && key == GLFW_KEY_S) {
        chosen = rail_L;
        next = jos_spre_donut;
    }
    if (I == Donut && key == GLFW_KEY_A) {
        chosen = rail_L2;
        next = jos_spre_donut;
    }
    if (I == lac_stanga && key == GLFW_KEY_D) {
        chosen = rail_O;
        next = I9;
    }
    if (I == lac_dreapta && key == GLFW_KEY_A) {
        chosen = rail_P;
        next = I9;
    }

    //daca totusi nu exista o sina valida nu se intampla nimic
    if (!chosen)
        return;

    //traseul final al trenului
    train.rail = chosen;
    train.from = I;
    train.to = next;

    if(I == I1 && chosen == rail_B) {
        train.forward = false;
        train.dist = chosen->length;
	}
    else {
        //din nou se verifica pozitia din care pleaca trenul. nu vrem ca trenul daca trebuie sa mearga de jos in sus sa aiba pozitia de start ca cea de sus
        Segment& first_seg = chosen->segments.front();

        if (glm::distance(first_seg.start, I->position) < glm::distance(first_seg.end, I->position)) {
            train.forward = true;
            train.dist = 0.0f;
        }
        else {
            train.forward = false;
            train.dist = chosen->length;
        }
    }

    //pun trenul in miscare
    train.stopped = false;
    //pleaca din intersectie deci schimb bool-ul in false
    train.waiting_At_intersection = false;
}


void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}