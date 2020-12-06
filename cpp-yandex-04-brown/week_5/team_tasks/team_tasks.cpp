#include <string>
#include <map>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

TaskStatus Next(TaskStatus status) {
  return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void RemoveZeros(TasksInfo& tasks_info) {
  for (auto it = tasks_info.begin(); it != tasks_info.end();) {
    if (it->second == 0) {
      it = tasks_info.erase(it);
    } else {
      it++;
    }
  }
}

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return person_tasks_.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    person_tasks_[person][TaskStatus::NEW]++;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count)
  {
    TasksInfo updated_tasks, untouched_tasks;

    TasksInfo& tasks = person_tasks_[person];

    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status))
    {
      updated_tasks[Next(status)] = min(task_count, tasks[status]);
      task_count -= updated_tasks[Next(status)];
    }


    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status))
    {
      untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
      tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
    }

    tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

    RemoveZeros(updated_tasks);
    RemoveZeros(untouched_tasks);

    return {updated_tasks, untouched_tasks};
  }

private:
  map<string, TasksInfo> person_tasks_;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
