#ifndef TIMER_H
#define TIMER_H

#include <atomic>
#include <thread>
#include <mutex>

// Biến toàn cục (dùng chung)
extern std::atomic<bool> keeprunning;   // Điều khiển vòng lặp đồng hồ
extern std::atomic<bool> isTurnSkipped; // Đánh dấu chuyển lượt khi hết thời gian
extern int turnTimer;                   // Thời gian cho mỗi lượt chơi
extern int gameTimer;                   // Thời gian cho toàn ván đấu
extern std::mutex timerMutex;           // Bảo vệ các biến thời gian
extern std::thread timerThread;         // Luồng chạy timer
extern std::mutex screenMutex;
// Hàm đếm ngược thời gian (có thể được gọi từ bên ngoài nếu cần)
void CountdownTimer();

// Hàm khởi động timer
void StartTimer(int gameTime, int turnTime);

// Hàm dừng timer
void StopTimer();

#endif // TIMER_H
