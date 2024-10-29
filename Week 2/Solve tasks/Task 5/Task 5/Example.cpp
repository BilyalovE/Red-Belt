#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include "profailer.h"
#include "test_runner.h"
#include <string>
#include <cstdint>
#include <map>
#include <queue>

using namespace std;

class HotelManager{
public:

    void Book(const int64_t time, const string& hotel_name,
              const int client_id, const int room_count){
        current_time = time;
        hotel_book[hotel_name].Book({time, client_id, room_count});
    }
    
    int Clients(const string& hotel_name){
        return hotel_book[hotel_name].Clients();
    }
    
    int Rooms(const string& hotel_name){
        return hotel_book[hotel_name].Rooms();
    }
    
private:
    struct ClientsInfo{
        int64_t time_m;
        int client_id_m;
        int room_count_m;
    };
    
    static int64_t current_time;
    
    class HotelInfo {
    public:
        void Book(const ClientsInfo& client_info){
            ++cliet_book_num[client_info.client_id_m];
            total_book_rooms += client_info.room_count_m;
            clients_queue.push(client_info);
        }
        
        int Clients(){
            ToolHotel();
            return static_cast<int>(cliet_book_num.size());
        }
        
        int Rooms(){
            ToolHotel();
            return total_book_rooms;
        }

    private:
        // ключ - клиент, значение - число бронирований у каждого клиента в гостинице
        map<int, int> cliet_book_num;
        int total_book_rooms = 0;
        queue<ClientsInfo> clients_queue;
        
        void ToolHotel(){
            while(!clients_queue.empty()){
                if (current_time - clients_queue.front().time_m >= time_duration ){
                    total_book_rooms -= clients_queue.front().room_count_m;
                    int client_id = clients_queue.front().client_id_m;
                    --cliet_book_num[client_id];
                    if(cliet_book_num[client_id] == 0){
                        cliet_book_num.erase(client_id);
                    }
                    clients_queue.pop();
                }
                else{
                    break;
                }
            }
        }
        
    };
    map<string, HotelInfo> hotel_book;
    const static int time_duration = 86400;
};

// Инициализация статической переменной
int64_t HotelManager::current_time = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // число запросов Qmax = 10ˆ5
    int Q = 0;
    cin >> Q;
    string command = "";
    HotelManager manager;
    while(Q > 0){
        cin >> command;
        int64_t time = 0;
        string hotel_name = "";
        int client_id = 0, room_count = 0;
        if(command == "BOOK"){
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        }
        else if(command == "CLIENTS"){
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        }
        else if(command == "ROOMS"){
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << "\n";
        }
        else{
            cout << "неверная команда " << command << "\n";
            continue;
        }
        --Q;
    }
}
