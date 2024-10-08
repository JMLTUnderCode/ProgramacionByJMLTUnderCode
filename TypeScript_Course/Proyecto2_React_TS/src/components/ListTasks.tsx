import { Task } from './Task'

type ListTaskProps = {
	listTasks: string[]
	deleteTask: (taskIndex: number) => void
}

export const ListTasks = ({listTasks, deleteTask}: ListTaskProps) => {
  return (
	<div className="taskList">
		{listTasks.map((task, index) => (
			<Task key={index} task={task} deleteTask={() => deleteTask(index)}></Task>
		))}
	</div>
  )
}