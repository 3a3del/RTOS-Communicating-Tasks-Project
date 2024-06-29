import matplotlib.pyplot as plt

# Data extracted from the provided output
total_sent_messages = [1009, 1009, 1009, 1009, 1009, 1001]
average_periods = [97, 139, 181, 220, 259, 301]
total_blocked_messages = [2027, 1139, 647, 346, 144, 0]

sender_1_success = [350, 349, 336, 344, 328, 333]  # High priority
sender_2_success = [328, 336, 325, 340, 335, 332]  # Low priority
sender_3_success = [331, 324, 348, 325, 346, 336]  # Low priority

sender_1_blocked = [679, 370, 218, 110, 59, 0]  # High priority
sender_2_blocked = [688, 381, 225, 113, 51, 0]  # Low priority
sender_3_blocked = [660, 388, 204, 123, 34, 0]  # Low priority

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


