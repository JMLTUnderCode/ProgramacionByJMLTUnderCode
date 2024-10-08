import { useState } from "react";
 
export const AllApps = () => {

    const [newTasks, setNewTasks] = useState('');
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
            </div>
        </div>
    )
}