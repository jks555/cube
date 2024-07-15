#include <GL/gl.h>      
#include <GLFW/glfw3.h> 
#include <iostream>     
#include <cmath>        

float rotationAngle = 0.0f;     // 初始化旋转角度为0

// 绘制立方体的函数
void drawCube() {
    glBegin(GL_QUADS);          // 开始绘制四边形

    // 前面
    glColor3f(0.0f, 1.0f, 0.0f); // 设置颜色为绿色
    glVertex3f(-1.0f, -1.0f, 1.0f); // 左下
    glVertex3f(1.0f, -1.0f, 1.0f);  // 右下
    glVertex3f(1.0f, 1.0f, 1.0f);   // 右上
    glVertex3f(-1.0f, 1.0f, 1.0f);  // 左上

    // 后面
    glColor3f(0.0f, 1.0f, 0.0f); // 设置颜色为绿色
    glVertex3f(-1.0f, -1.0f, -1.0f); // 左下
    glVertex3f(1.0f, -1.0f, -1.0f);  // 右下
    glVertex3f(1.0f, 1.0f, -1.0f);   // 右上
    glVertex3f(-1.0f, 1.0f, -1.0f);  // 左上

    // 左面
    glColor3f(1.0f, 1.0f, 0.0f); // 设置颜色为黄色
    glVertex3f(-1.0f, -1.0f, -1.0f); // 后下
    glVertex3f(-1.0f, -1.0f, 1.0f);  // 前下
    glVertex3f(-1.0f, 1.0f, 1.0f);   // 前上
    glVertex3f(-1.0f, 1.0f, -1.0f);  // 后上

    // 右面
    glColor3f(1.0f, 1.0f, 0.0f); // 设置颜色为黄色
    glVertex3f(1.0f, -1.0f, -1.0f); // 后下
    glVertex3f(1.0f, -1.0f, 1.0f);  // 前下
    glVertex3f(1.0f, 1.0f, 1.0f);   // 前上
    glVertex3f(1.0f, 1.0f, -1.0f);  // 后上

    // 上面
    glColor3f(0.0f, 1.0f, 0.0f); // 设置颜色为绿色
    glVertex3f(-1.0f, 1.0f, 1.0f);  // 前左
    glVertex3f(1.0f, 1.0f, 1.0f);   // 前右
    glVertex3f(1.0f, 1.0f, -1.0f);  // 后右
    glVertex3f(-1.0f, 1.0f, -1.0f); // 后左

    // 底面
    glColor3f(1.0f, 1.0f, 0.0f); // 设置颜色为黄色
    glVertex3f(-1.0f, -1.0f, -1.0f); // 后左
    glVertex3f(1.0f, -1.0f, -1.0f);  // 后右
    glVertex3f(1.0f, -1.0f, 1.0f);   // 前右
    glVertex3f(-1.0f, -1.0f, 1.0f);  // 前左

    glEnd();                    // 结束绘制
}

// 设置立方体的投影矩阵
void setCube(int width, int height) {
    glViewport(0, 0, width, height);    // 设置视口
    glMatrixMode(GL_PROJECTION);        // 选择投影矩阵
    glLoadIdentity();                   // 重置当前矩阵

    float aspectRatio = (float) width / (float) height;   // 计算宽高比
    float fieldAngle = 60.0f;           // 视角角度，单位为度
    float nearAngle = 0.1f;             // 近裁剪面
    float farAngle = 100.0f;            // 远裁剪面

    // 计算透视投影矩阵
    float f = 1.0f / tanf((fieldAngle / 2.0f) * (M_PI / 180.0f));
    float Matrix[] = {
        f / aspectRatio, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (farAngle + nearAngle) / (nearAngle - farAngle), -1.0f,
        0.0f, 0.0f, (2.0f * farAngle * nearAngle) / (nearAngle - farAngle), 0.0f
    };

    glMultMatrixf(Matrix);    // 应用投影矩阵
    glMatrixMode(GL_MODELVIEW);         // 选择模型视图矩阵
    glLoadIdentity();                   // 重置当前矩阵
}

int main() {
    GLFWwindow* window;

    // 初始化GLFW库
    if (!glfwInit())
        return -1;

    // 创建一个窗口和其OpenGL上下文
    window = glfwCreateWindow(800, 600, "正方体展示", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 将窗口的上下文设置为当前上下文
    glfwMakeContextCurrent(window);

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 循环，直到关闭窗口
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // 渲染
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 设置投影矩阵和视口
        setCube(width, height);

        // 设置模型视图矩阵
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        
        // 绕Y轴旋转立方体
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

        // 绘制立方体
        drawCube();

        // 增加旋转角度以便下一帧
        rotationAngle += 0.5f;

        // 交换前后缓冲区
        glfwSwapBuffers(window);

        // 处理事件
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
