#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks_.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person) {
        ++tasks_[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated;
        TasksInfo untouched;
        
        if (tasks_.count(person) == 0) {
            return {};
        }
        
        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
            const int to_update_counter = tasks_[person][status] - updated[status];
            const int updated_counter = min(task_count, to_update_counter);
            
            updated[Next(status)] = updated_counter;
            tasks_[person][Next(status)] += updated_counter;
            tasks_[person][status] -= updated_counter;
            task_count -= updated_counter;
            
            untouched[status] = to_update_counter - updated_counter;
        }
        
        return { updated, untouched };
    }
    
private:
    map<string, TasksInfo> tasks_;
    
    static TaskStatus Next(TaskStatus task_status) {
        return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"s
         << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
         << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
         << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia"s);
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan"s);
    }
    cout << "Ilia's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"s));
    cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
    
    TeamTasks tasks2;
    tasks2.AddNewTask("Sasha");
    tasks2.AddNewTask("Sasha");
    tasks2.AddNewTask("Sasha");
  
    TasksInfo updated_tasks2, untouched_tasks2;
    for (int i = 0; i != 4; ++i) {
        tie(updated_tasks2, untouched_tasks2) = tasks2.PerformPersonTasks("Sasha", 10);
        cout << "Updated Sasha's tasks: ";
        PrintTasksInfo(updated_tasks2);
        cout << "Untouched Sasha's tasks: ";
        PrintTasksInfo(untouched_tasks2);
    }
}
