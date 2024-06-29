import matplotlib.pyplot as plt

# Data extracted from the provided output for Queue size 3
total_sent_messages = [1002, 1002, 1002, 1002, 1002, 1001]
average_periods = [99, 138, 180, 220, 258, 303]
total_blocked_messages = [2034, 1146, 654, 353, 153, 10]

sender_1_success = [348, 346, 336, 318, 328, 331]  # High priority
sender_2_success = [332, 343, 321, 347, 335, 334]  # Low priority
sender_3_success = [322, 313, 345, 337, 339, 336]  # Low priority

sender_1_blocked = [657, 374, 219, 136, 59, 4]  # High priority
sender_2_blocked = [688, 379, 232, 104, 49, 4]  # Low priority
sender_3_blocked = [689, 393, 203, 113, 45, 2]  # Low priority

# Total Sent Messages vs. Average Sender Timer Period
plt.figure(num=1)
plt.plot(average_periods, total_sent_messages, marker='o')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Total Sent Messages')
plt.title('Figure 1: Total Sent Messages vs Average Sender Timer Period')
plt.grid(True)
plt.show()

# Total Blocked Messages vs. Average Sender Timer Period
plt.figure(num=2)
plt.plot(average_periods, total_blocked_messages, marker='o')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Total Blocked Messages')
plt.title('Figure 2: Total Blocked Messages vs Average Sender Timer Period')
plt.grid(True)
plt.show()

# Successful Messages for Each Sender Task
plt.figure(num=3)
plt.plot(average_periods, sender_1_success, marker='o', label='Sender 1 Success (High Priority)')
plt.plot(average_periods, sender_2_success, marker='o', label='Sender 2 Success (Low Priority)')
plt.plot(average_periods, sender_3_success, marker='o', label='Sender 3 Success (Low Priority)')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Successful Messages')
plt.title('Figure 3: Successful Messages per Sender Task')
plt.legend()
plt.grid(True)
plt.show()

# Blocked Messages for Each Sender Task
plt.figure(num=4)
plt.plot(average_periods, sender_1_blocked, marker='o', label='Sender 1 Blocked (High Priority)')
plt.plot(average_periods, sender_2_blocked, marker='o', label='Sender 2 Blocked (Low Priority)')
plt.plot(average_periods, sender_3_blocked, marker='o', label='Sender 3 Blocked (Low Priority)')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Blocked Messages')
plt.title('Figure 4: Blocked Messages per Sender Task')
plt.legend()
plt.grid(True)
plt.show()

# Detailed plot for Sender 1 (High Priority)
plt.figure(num=5)
plt.plot(average_periods, sender_1_success, marker='o', label='Succeeded')
plt.plot(average_periods, sender_1_blocked, marker='o', label='Blocked')
plt.plot(average_periods, [s + b for s, b in zip(sender_1_success, sender_1_blocked)], marker='o', label='Total Sent')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Messages')
plt.title('Figure 5: Sender 1 (High Priority) Messages')
plt.legend()
plt.grid(True)
plt.show()

# Detailed plot for Sender 2 (Low Priority)
plt.figure(num=6)
plt.plot(average_periods, sender_2_success, marker='o', label='Succeeded')
plt.plot(average_periods, sender_2_blocked, marker='o', label='Blocked')
plt.plot(average_periods, [s + b for s, b in zip(sender_2_success, sender_2_blocked)], marker='o', label='Total Sent')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Messages')
plt.title('Figure 6: Sender 2 (Low Priority) Messages')
plt.legend()
plt.grid(True)
plt.show()

# Detailed plot for Sender 3 (Low Priority)
plt.figure(num=7)
plt.plot(average_periods, sender_3_success, marker='o', label='Succeeded')
plt.plot(average_periods, sender_3_blocked, marker='o', label='Blocked')
plt.plot(average_periods, [s + b for s, b in zip(sender_3_success, sender_3_blocked)], marker='o', label='Total Sent')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Messages')
plt.title('Figure 7: Sender 3 (Low Priority) Messages')
plt.legend()
plt.grid(True)
plt.show()

