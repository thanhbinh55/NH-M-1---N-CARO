#include "DrawTest.h"


void drawBlock(int x, int y, int color) {
    SetColor(0, color); // Đặt màu nền
    GotoXY(x, y);
    cout << "  "; // Hai khoảng trống để tạo ra khối vuông
}
void drawC(int startX, int startY, int color) {
    for (int x = 1; x < 5; ++x) {
        drawBlock(startX + x * 2, startY, color);
        drawBlock(startX + x * 2, startY + 6, color);
    }
    for (int y = 1; y < 6; ++y) {
        drawBlock(startX, startY + y, color);
    }
}

void drawL(int startX, int startY, int color) {
    for (int y = 0; y < 7; ++y) {
        drawBlock(startX, startY + y, color); // Cột bên trái
    }
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY + 6, color); // Đường ngang dưới
    }
}

void drawS(int startX, int startY, int color) {
    // Vẽ đường ngang trên
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY, color);
    }
    // Vẽ cột bên trái
    drawBlock(startX, startY + 1, color);
    drawBlock(startX, startY + 2, color);
    // Vẽ đường ngang giữa
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY + 3, color);
    }
    // Vẽ cột bên phải
    drawBlock(startX + 8, startY + 4, color);
    drawBlock(startX + 8, startY + 5, color);
    // Vẽ đường ngang dưới
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY + 6, color);
    }
}

void drawE(int startX, int startY, int color) {
    for (int y = 0; y < 7; ++y) {
        drawBlock(startX, startY + y, color); // Cột bên trái
    }
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY, color); // Đỉnh
        drawBlock(startX + x * 2, startY + 3, color); // Giữa
        drawBlock(startX + x * 2, startY + 6, color); // Đáy
    }
}

void drawA(int startX, int startY, int maincolor, int borderColor) {
    drawBlock(startX - 1, startY + 1, borderColor); // Trên cùng bên trái
    drawBlock(startX - 1, startY + 2, borderColor);
    drawBlock(startX - 1, startY + 3, borderColor);
    drawBlock(startX - 1, startY + 4, borderColor); // Giữa
    drawBlock(startX - 1, startY + 5, borderColor); // Dưới cùng
    drawBlock(startX - 1, startY + 6, borderColor); // Bỏ qua phần ngang giữa

    // Viền bên phải
    drawBlock(startX + 9, startY + 1, borderColor); // Trên cùng bên phải
    drawBlock(startX + 9, startY + 2, borderColor);
    drawBlock(startX + 9, startY + 3, borderColor);
    drawBlock(startX + 9, startY + 4, borderColor); // Giữa
    drawBlock(startX + 9, startY + 5, borderColor); // Dưới cùng
    drawBlock(startX + 9, startY + 6, borderColor); // Bỏ qua phần ngang giữa

    // Vẽ đường chéo cho viền
    drawBlock(startX + 1, startY, borderColor); // Đường chéo trái
    drawBlock(startX + 2, startY, borderColor);
    drawBlock(startX + 3, startY, borderColor);
    drawBlock(startX + 4, startY, borderColor);
    drawBlock(startX + 5, startY, borderColor);
    drawBlock(startX + 7, startY, borderColor);
    // Vẽ thân bên trái và phải của chữ "A"
    for (int y = 1; y < 7; ++y) {
        drawBlock(startX, startY + y, maincolor);         // Cột trái
        drawBlock(startX + 8, startY + y, maincolor);     // Cột phải
    }

    // Vẽ phần đỉnh của chữ "A"
    drawBlock(startX + 2, startY, maincolor); // Đỉnh trái
    drawBlock(startX + 3, startY, maincolor); // Đỉnh trái
    drawBlock(startX + 4, startY, maincolor); // Đỉnh trái
    drawBlock(startX + 5, startY, maincolor); // Đỉnh trái
    drawBlock(startX + 6, startY, maincolor); // Đỉnh phải

    // Vẽ phần ngang giữa chữ "A"
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x * 2, startY + 3, maincolor); // Ngang giữa
    }
}

void drawR(int startX, int startY, int color) {
    for (int y = 0; y < 7; ++y) {
        drawBlock(startX, startY + y, color);
    }
    for (int x = 1; x < 4; ++x) {
        drawBlock(startX + x * 2, startY, color);
        drawBlock(startX + x * 2, startY + 3, color);
    }
    drawBlock(startX + 8, startY + 1, color);
    drawBlock(startX + 8, startY + 2, color);
    drawBlock(startX + 4, startY + 4, color);
    drawBlock(startX + 6, startY + 5, color);
    drawBlock(startX + 8, startY + 6, color);
}

void drawO(int startX, int startY, int color) {
    for (int x = 1; x < 4; ++x) {
        drawBlock(startX + x * 2, startY, color);
        drawBlock(startX + x * 2, startY + 6, color);
    }
    for (int y = 1; y < 6; ++y) {
        drawBlock(startX, startY + y, color);
        drawBlock(startX + 8, startY + y, color);
    }
}

void drawW(int startX, int startY, int borderColor) {

    // Vẽ chữ "W" chính
    for (int y = 0; y < 4; ++y) {
        drawBlock(startX, startY + y, borderColor); // Cạnh bên trái
        //drawBlock(startX + 4, startY + y, borderColor); // Đường giữa
        drawBlock(startX + 10, startY + y, borderColor); // Cạnh bên phải
    }
    drawBlock(startX + 1, startY + 4, borderColor);
    drawBlock(startX + 3, startY + 3, borderColor);
    drawBlock(startX + 5, startY + 2, borderColor);
    drawBlock(startX + 7, startY + 3, borderColor);
    drawBlock(startX + 9, startY + 4, borderColor);
}

void drawI(int startX, int startY, int color) {
    // Vẽ chữ "I"
    for (int y = 0; y < 5; ++y) {
        drawBlock(startX, startY + y, color);
    }
    drawBlock(startX, startY + 3, color); // Đường ngang giữa
}

void drawN(int startX, int startY, int mainColor, int borderColor) {
    // Vẽ viền
    drawBlock(startX - 1, startY, borderColor); // Trên cùng bên trái
    drawBlock(startX - 1, startY + 1, borderColor);
    drawBlock(startX - 1, startY + 2, borderColor);
    drawBlock(startX - 1, startY + 3, borderColor);
    drawBlock(startX - 1, startY + 4, borderColor); // Dưới cùng bên trái

    drawBlock(startX + 6, startY, borderColor); // Trên cùng bên phải
    drawBlock(startX + 6, startY + 1, borderColor);
    drawBlock(startX + 6, startY + 2, borderColor);
    drawBlock(startX + 6, startY + 3, borderColor);
    drawBlock(startX + 6, startY + 4, borderColor); // Dưới cùng bên phải

    // Đường chéo cho viền
    drawBlock(startX + 1, startY + 1, borderColor);
    drawBlock(startX + 2, startY + 2, borderColor);
    drawBlock(startX + 3, startY + 3, borderColor);
    drawBlock(startX + 4, startY + 4, borderColor);

    // Vẽ chữ "N" chính
    for (int y = 0; y < 5; ++y) {
        drawBlock(startX, startY + y, mainColor); // Cạnh bên trái
        drawBlock(startX + 6, startY + y, mainColor); // Cạnh bên phải
    }
    for (int x = 0; x < 5; ++x) {
        drawBlock(startX + x + 1, startY + x, mainColor); // Đường chéo
    }
}


void LogoCaro(int startX, int startY) {

    drawC(startX, startY, 3); // Màu xanh dương
    drawA(startX + 12, startY, 3, 0); // Màu xanh lá
    drawR(startX + 24, startY, 3); // Màu đỏ
    drawO(startX + 36, startY, 3); // Màu vàng

    SetColor(0, 15); // Reset color to default
}


void printLogo(int x)
{
    SetColor(4, x);
    unsigned char logo[] = {
        32,219,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,32,32,32,32,32,219,219,219,219,219,219,187,32,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,219,219,219,219,219,219,187,32,
219,219,201,205,205,205,205,188,219,219,201,205,205,205,219,219,187,32,32,32,32,32,219,219,201,205,205,205,205,188,219,219,201,205,205,219,219,187,219,219,201,205,205,219,219,187,219,219,201,205,205,205,219,219,187,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,219,219,219,219,219,186,219,219,219,219,219,219,201,188,219,219,186,32,32,32,219,219,186,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,219,219,186,32,32,32,219,219,186,
200,219,219,219,219,219,219,187,200,219,219,219,219,219,219,201,188,32,32,32,32,32,200,219,219,219,219,219,219,187,219,219,186,32,32,219,219,186,219,219,186,32,32,219,219,186,200,219,219,219,219,219,219,201,188,
32,200,205,205,205,205,205,188,32,200,205,205,205,205,205,188,32,32,32,32,32,32,32,200,205,205,205,205,205,188,200,205,188,32,32,200,205,188,200,205,188,32,32,200,205,188,32,200,205,205,205,205,205,188,32 };
    int top = 4, left = 50;
    int num_lines = 6, num_chars = 55;
    for (int i = 0; i < num_lines; i++)
    {
        GotoXY(left, i + top);
        for (int j = 0; j < num_chars; j++)
            putchar(logo[i * num_chars + j]);
    }
}