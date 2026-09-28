import numpy as np
from matplotlib import pyplot as plt

days = np.array([1, 2, 3, 4, 5, 6, 7])
total_bananas_eaten = np.array([2, 5, 7, 9, 11, 13, 16])

plt.scatter(days,total_bananas_eaten)
plt.xlabel("dag")
plt.ylabel("bananen")


weight = 0.

def model(x):
    return x * weight

def loss_function(y_pred,y_real):
    return ((y_pred-y_real)**2).mean()

training_steps = 100
learning_rate = 0.01

weight_tracker = []
loss_tracker = []

for step in range(training_steps):
    banana_pred = model(days)
    loss = loss_function(banana_pred, total_bananas_eaten)
    loss_tracker.append(loss)

    gradient = 1/len(days)*2*sum((weight*days-total_bananas_eaten)*days) #gradient, dloss_function/dweight
    weight -= learning_rate*gradient
    weight_tracker.append(weight)




#visualization

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

for i in range(len(weight_tracker)):
    ax1.cla()
    ax2.cla()

    ax1.scatter(days, total_bananas_eaten, label="true values")
    ax1.plot(days, weight_tracker[i] * days, label=f"Prediction - Epoch No {i+1}")
    ax1.set_title(f"Weight = {weight_tracker[i]:.2f}")
    ax1.grid()
    ax1.legend()

    ax2.plot(weight_tracker, loss_tracker, label="Loss curve")
    ax2.scatter(weight_tracker[i], loss_tracker[i], color='red', label="Current Point")
    ax2.set_title("Loss vs Weight")
    ax2.grid()
    ax2.legend()

    plt.pause(0.5)
    plt.draw()

plt.show()