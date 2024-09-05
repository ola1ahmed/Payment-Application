# Payment-Application

## Project Software Architecture:
![flowchart](https://github.com/user-attachments/assets/ac499a4a-9dd4-4f7b-8bd5-ef8047acb96d)

## Folder Structure:
```bash
└───PaymentApplication
│   └───CARD
│       └─── card.h
│       └─── card.c
│   └───TERMINAL
│       └─── terminal.h
│       └─── terminal.c
│   └───SERVER
│       └─── server.h
│       └─── server.c
│   └───APP
│       └─── app.h
│       └─── app.c
│	└─── main.c
│   └───FILE_HANDLING
│       └─── File_handling.h
│       └─── File_handling.c
│	└─── database.c
│   └───Data_Structure
│       └─── linkedlist.h
│       └─── linkedlist.h
│	└─── queue.c
│	└─── queue.h
│	└─── stack.c
│	└─── stack.h
│   └───Library
│	└─── STD_TYPES.h
│   └───accounts.txt
│   └───transactions.txt
│   └───my_program.exe

```
## Functionality:
The Payment Application project offers the following features:

### Card Module:
This module is responsible for handling card-related operations, such as reading card information and validating transactions.
### Terminal Module:
The terminal module manages the interaction between the card and the application. It processes user inputs and sends commands to the card.
### Server Module:
This module acts as the backend of the application, handling transaction requests, processing payments, and managing transaction logs.
### App Module:
The main application module brings together the card, terminal, and server modules to perform complete transaction procedures. It serves as the user interface and orchestrates the entire payment process.
