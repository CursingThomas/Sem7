#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;
int avgExec = 0;

int prev_rx = 0;
int prev_tx = 0;

int total_bytes = 0;
bool flag = 0;
int main () {

for(int i = 1; i > 0; i++) 
{
auto start = high_resolution_clock::now();

std::ifstream rx_bytes; rx_bytes.open("/sys/class/net/lo/statistics/rx_bytes");
std::string rx_String;

std::ifstream tx_bytes; tx_bytes.open("/sys/class/net/lo/statistics/tx_bytes");
std::string tx_String;

if ( rx_bytes.is_open() && tx_bytes.is_open()) { // always check whether the file is open
rx_bytes >> rx_String;

tx_bytes >> tx_String;

int curr_rx = stoi(rx_String);
int curr_tx = stoi(rx_String);


total_bytes = total_bytes + (curr_rx - prev_rx);

if (flag == 0)
{
    total_bytes = 0;
}

std::cout << (curr_rx - prev_rx) << std::endl;
std::cout << (curr_tx - prev_tx) << std::endl;
std::cout << total_bytes << std::endl;
prev_rx = curr_rx;
prev_tx = curr_tx;



}
auto stop = high_resolution_clock::now();

auto duration = duration_cast<microseconds>(stop - start);
std::cout << duration.count() << std::endl;

if (avgExec == 0)
{
    avgExec = duration.count();
}
avgExec = (avgExec + duration.count()) / 2;
flag = 1;
sleep_for(microseconds(1000000 - avgExec));

}

return 0;
}

