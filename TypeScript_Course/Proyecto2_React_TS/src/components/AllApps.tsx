import { useState } from "react";
import { ListTasks } from "./ListTasks";

export const AllApps = () => {
    const [newTasks, setNewTasks] = useState<string>('');
    const [listTasks, setListTasks] = useState<string[]>([]);
    const handleAddTask = () => {
        if (newTasks.trim() !== '') {
            setListTasks(lastTasks => [...lastTasks, newTasks]);
            setNewTasks('');
        }
    }
    const handleDeleteTask = (taskIndex: number) => {
        setListTasks(currentTask => currentTask.filter((_, index) => index !== taskIndex));
    }

    return (
        <div>
            <h1>Tasks Manager</h1>
            <div>
                <input
                    type = "text"
                    value = {newTasks}
                    onChange = {(event) => setNewTasks(event.target.value)}
                    placeholder = "New Task"
                />
                <button style={{margin: "auto"}} onClick={handleAddTask}>Add Task</button>
                
            </div>
        <ListTasks listTasks={listTasks} deleteTask={handleDeleteTask}></ListTasks>
        </div>
    )
}