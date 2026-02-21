#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"

namespace m1
{
    struct Intersection;

    struct Segment {
        glm::vec3 start;
        glm::vec3 end;
        float length;
    };

    struct Rail {
        std::vector<Segment> segments;
        float length;
        Intersection* inters_A = nullptr;
		Intersection* inters_B = nullptr;
    };

    struct Intersection {
        glm::vec3 position;
        std::vector<Rail*> connected_rails;
        bool is_terminal = false;
    };

    enum TrainDir {
        DIR_RIGHT,
		DIR_LEFT,
        DIR_UP,
		DIR_DOWN
    };

    struct Train {
        Rail* rail;
        Intersection* from;
        Intersection* to;
        float dist;
        bool stopped;
        bool forward;
		bool waiting_At_intersection = false;
		TrainDir dir;   
    };

    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    private:
		gfxc::Camera* camera;
		glm::mat4 projectionMatrix;
        std::vector<Rail*> rails;
        Train train;

		Segment s1, s2, s3_i, s3_ii, s4_i, s4_ii, s5, s6, s7_i, s7_ii, s8, s9, s10, s11, s12, s13, s14, s15_i, s15_ii,
            s16, s17, s18, s19, s20, s21, s22, s23, s24_i, s24_ii, s25, s26, s27,
			s28, s29, s30_i, s30_ii, s30_iii, s30_iv, s31, s32_i, s32_ii, s33, s34, s35, s36_i, s36_ii;
		Intersection *I1, *I2, *I3, *I4, *I5, *I6, *I7, *I8, *I9, *I10, *I11, *Donut, *Box, *Pyramid, *Sphere, *jos_spre_donut, *spre_piramida, *stanga_sus, *stanga_jos, *lac_stanga, *lac_dreapta;
		Rail *rail_A, *rail_A1, *rail_A2, *rail_B, *rail_B2, *rail_C, *rail_D, *rail_E, *rail_F, *rail_G, *rail_H, *rail_I, *rail_J, *rail_K, *rail_L, *rail_L2, *rail_M,
            *rail_N, *rail_O, *rail_O1, *rail_P, *rail_P1, *rail_Q, *rail_R, *rail_S, *rail_S2;
		
        glm::vec3 train_pos;
        int k = 0;
        float timer_total = 0.0f;
        int current_sphere = 0;
        bool black_screen = false;
        float endscreen = 0.0f;
        int generate_command = 0;
        int v[5];
		bool command1_done = false;
		bool command2_done = false;
		bool command3_done = false;
		bool command4_done = false;
		bool command5_done = false;
		int command1, command2, command3, command4, command5;
        int current_command = 0;
        glm::vec3 target;
		float c1x, c1y, c1z, c2x, c2y, c2z, c3x, c3y, c3z, c4x, c4y, c4z, c5x, c5y, c5z;
        glm::vec3 command_now[5];

    };
}
