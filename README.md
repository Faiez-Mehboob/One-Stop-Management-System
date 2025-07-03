# 🛠️ One Stop Management System

This is a C++ project developed for the **Data Structures** course. The **One Stop Management System** acts as a digital helpdesk platform for managing and resolving student service requests within a university. It uses core data structures to simulate real-world request tracking and resolution.


## 🎯 Features

- 🎟️ **Ticket Management**
  - Add/remove tickets with unique IDs
  - Track ticket status (open, assigned, closed)
  - Priority-based sorting (using bubble, selection, insertion, merge, or quick sort)
  - Binary & interpolation search for tickets

- 🧑‍💼 **Agent Management**
  - Add support agents
  - Assign tickets in round-robin based on load
  - Maximum 5 tickets per agent
  - Ticket resolution with logging

- 📊 **Reports & Analytics**
  - View all open tickets
  - View resolution log (LIFO using stack)
  - View agents and their assigned tickets

- ⚙️ **Configuration Support**
  - Reads default sort/search options from `config.txt`
  - Dynamically selects sorting based on ticket size threshold


## 📂 File Structure

- `One_Stop_Management_System.cpp` — Main source file
- `config.txt` — (Optional) Configure default sorting and searching methods
- Tickets and agent data handled in memory using appropriate structures


## 💻 Usage

1. **Compile the program**
   ```bash
   g++ One_Stop_Management_System.cpp -o one_stop

2. **Run the executable**
   - ./one_stop
     
3. **Interact through the menu**
   - Choose from Ticket Management, Agent Management, or Report & Analytics
   - Follow on-screen prompts to manage system

## 📘 Data Structures Used

- Linked List – For ticket storage and traversal
- Stack – For resolution logs (LIFO order)
- Queue (via sorted vector) – For ticket assignment
- Vector – To manage agents, tickets, and log history

## 🔮 Future Enhancements

- Add persistent file/database storage
- GUI or web-based interface
- Authentication system for agents
- Email notifications for ticket status

## 📃 License

- This project is provided for academic and educational use only.
