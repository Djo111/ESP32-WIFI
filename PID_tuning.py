# import socket
# import matplotlib.pyplot as plt
# import numpy as np

# HOST = ''    # empty string means listen on all available interfaces
# PORT = 1234  # arbitrary port number, must match the port number in the ESP32 program




# # create a figure and axis object
# fig, ax = plt.subplots()

# # initialize an empty line object
# line, = ax.plot([], [])

# # set axis limits and labels
# ax.set_xlim(0, 10)
# ax.set_ylim(0, 1)
# ax.set_xlabel('Time')
# ax.set_ylabel('Process Variable')

# # define a function to update the plot
# def update_plot(data):
#     x, y = data
#     line.set_data(x, y)
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# # main loop that receives data from the socket and updates the plot
# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.bind((HOST, PORT))
#     s.listen()
#     conn, addr = s.accept()
#     with conn:
#         print('Connected by', addr)
#         x = []
#         y = []
#         while True:
#             data = conn.recv(1024)
#             if not data:
#                 break
#             value = float(data.decode())
#             x.append(len(y))
#             y.append(value)
#             if len(x) > 10:
#                 x = x[-10:]
#                 y = y[-10:]
#             update_plot((x, y))





# import numpy as np
# import matplotlib.pyplot as plt



# # Set the desired display window size
# window_size = 100

# # Create an empty figure and axis with labels
# fig, ax = plt.subplots()
# ax.set_xlabel('Time (s)')
# ax.set_ylabel('Process Variable')

# # Create an empty line object to update with new data
# line, = ax.plot([], [])
# ax.axhline(y=0, color='r')
# # Define empty arrays to store x and y data
# xdata = []
# ydata = []

# # Define a function to update the plot with new data
# def update_plot():
#     # store the real-time data in y
#     y = np.random.uniform(low=-40, high=40)
    
#     # Add the new data point to the arrays
#     xdata.append(xdata[-1] + 1 if len(xdata) > 0 else 0)
#     ydata.append(y)
    
#     # Truncate the data arrays to the desired window size
#     xdata_truncated = xdata[-window_size:]
#     ydata_truncated = ydata[-window_size:]
    
#     # Update the line data
#     line.set_data(xdata_truncated, ydata_truncated)
    
#     # Set the x-axis limit to show the desired display window size
#     right_boundary = max(xdata_truncated) if len(xdata_truncated) > 0 else 0
#     left_boundary = max(right_boundary - window_size, 0)
#     ax.set_xlim(left_boundary, right_boundary)
    
#     # Set the y-axis limit to always show the range of data
#     ax.set_ylim(-50, 50)
    
#     # Redraw the canvas and flush any pending events
#     fig.canvas.draw()
#     fig.canvas.flush_events()

# # Continuously update the plot with new data
# while True:
#     update_plot()
#     plt.pause(0.1)





import socket
import numpy as np
import matplotlib.pyplot as plt
#import warnings
#warnings.filterwarnings("ignore", message="Attempting to set identical")

HOST = ''    # empty string means listen on all available interfaces
PORT = 1234  # arbitrary port number, must match the port number in the ESP32 program

hostname = socket.gethostname()
ip_address = socket.gethostbyname(hostname)

print("Hostname:", hostname)
print("IP Address:", ip_address)

# Set the desired display window size
window_size = 100

# Create an empty figure and axis with labels
fig, ax = plt.subplots()
ax.set_xlabel('Time (s)')
ax.set_ylabel('Process Variable')

# Create an empty line object to update with new data
line, = ax.plot([], [])
ax.axhline(y=0, color='r')
# Define empty arrays to store x and y data
xdata = []
ydata = []

# Define a function to update the plot with new data
def update_plot(data):
    # store the real-time data in y
    y = data
    if len(y) > 0:
        # store the real-time data in y
        latest_y = y[-1]
       # print(latest_y)
    # Add the new data point to the arrays
    xdata.append(xdata[-1] + 1 if len(xdata) > 0 else 0)
    ydata.append(latest_y)
    
    # Truncate the data arrays to the desired window size
    xdata_truncated = xdata[-window_size:]
    ydata_truncated = ydata[-window_size:]
    
    # Update the line data
    line.set_data(xdata_truncated, ydata_truncated)
    
    # Set the x-axis limit to show the desired display window size
    right_boundary = max(xdata_truncated) if len(xdata_truncated) > 0 else 0
    left_boundary = max(right_boundary - window_size, 0)
    ax.set_xlim(left_boundary, right_boundary)
    
    # Set the y-axis limit to always show the range of data
    ax.set_ylim(-90, 90)
    
    # Redraw the canvas and flush any pending events
    fig.canvas.draw()
    fig.canvas.flush_events()
    



# main loop that receives data from the socket and updates the plot
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        y = []
        while True:
            conn, addr = s.accept()
            #data = conn.recv(2)  # receive 2 bytes (int16_t)
            data = conn.recv(1024)  # receive available data
            #print(data)
            if not data:
                break
            #value = float(data.decode())
            
            value = int.from_bytes(data, byteorder='little', signed=True)  # convert the received bytes to an integer
            print("Received value:", value)
            #values = np.frombuffer(data, dtype=np.int16)  # convert the received bytes to integers
            #print("Received values:", values)
            
            #for value in values:
             #   y.append(value)
            y.append(value)
            
            update_plot(y)
            
            plt.pause(0.000000000000000000000000000000000000000000000000000000000001) #set the time to synchronize data flow 0.00000000000000000000001