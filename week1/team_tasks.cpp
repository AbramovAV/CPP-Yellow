#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
      return persons_tasks.at(person);
  }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
      persons_tasks[person][TaskStatus::NEW]++;
  }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
        map<TaskStatus,int> updated_tasks;
        map<TaskStatus,int> untouched_tasks;

        if(persons_tasks.count(person)>0){
          for(const auto& [task,num_tasks]: persons_tasks[person]){
              int tasks_update = min(num_tasks,task_count);
              switch (task)
              {
              case TaskStatus::NEW:
                  updated_tasks[TaskStatus::IN_PROGRESS]+=tasks_update;
                  untouched_tasks[TaskStatus::NEW]+=(num_tasks-tasks_update);
                  break;
              case TaskStatus::IN_PROGRESS:
                  updated_tasks[TaskStatus::TESTING]+=tasks_update;
                  untouched_tasks[TaskStatus::IN_PROGRESS]+=(num_tasks-tasks_update);
                  break;
              case TaskStatus::TESTING:
                  updated_tasks[TaskStatus::DONE]+=tasks_update;
                  untouched_tasks[TaskStatus::TESTING]+=(num_tasks-tasks_update);
                  break;
              default:
                  continue;
                  break;
              }
              task_count-=tasks_update;
          }

          set<TaskStatus> tasks = {TaskStatus::NEW,TaskStatus::IN_PROGRESS,TaskStatus::TESTING};
          for(const auto& task: tasks){
              persons_tasks[person][task]=untouched_tasks[task];
              persons_tasks[person][task]+=updated_tasks[task];
              if(persons_tasks[person][task]==0) persons_tasks[person].erase(task);
              if(untouched_tasks[task]==0) untouched_tasks.erase(task);
              if(updated_tasks[task]==0) updated_tasks.erase(task);
          }
          if(updated_tasks[TaskStatus::DONE]>0){
              persons_tasks[person][TaskStatus::DONE]+=updated_tasks[TaskStatus::DONE];
          } else{
              updated_tasks.erase(TaskStatus::DONE);
          }
        }
        return tie(updated_tasks, untouched_tasks);
      }
private:
    map<string,TasksInfo> persons_tasks;
};
