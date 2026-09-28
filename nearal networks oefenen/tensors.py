import numpy as np
import torch

data = [[1.,2.,3.], [4.,5.,6.]]
data_shape = (2,5)
tensor_data = torch.tensor(data)

tensor_ones = torch.ones_like(tensor_data)
tensor_rand_same_shape_as_data = torch.rand_like(tensor_data, dtype = torch.float)
tensor_rand = torch.rand(data_shape)

tensor_rand[:,1] = 0.
tensor_rand[0,0] = 67.

tensor_combined = torch.cat([tensor_rand, tensor_ones], dim = 1)

multiplied = tensor_data @ tensor_data.T # .T (transpose) switched rij en colom, dus een 3x2 wordt een 2x3, waardoor vermenigvoudiging mogenlijk is
multiplied_but_differen_notation = tensor_data.matmul(tensor_data.T)

# (rij,collom), voor multiplicatie (2,3)*(3,2) moeten de binnenste getallen hetzelfde zijn, voor elke collom een rij om mee te vermenigvuldigen, en de dimenties van het resultaat zijn de buitenste 2, dus (2,2)

tensor_out = torch.rand_like(multiplied, dtype = torch.float)
torch.matmul(tensor_data, tensor_data.T, out = tensor_out) #stores ouput in tensor_out

dot_product = tensor_data * tensor_data
dot_product_differnt_notation = torch.mul(tensor_data, tensor_data)

agg = tensor_data.sum() #agg = aggregeren = samenvoegen = bij elkaar optellen
agg_item = agg.item()   #.item() maakt van een tensor met 1 waarde een normale python waarde 

bigger_data = tensor_data.add_(5)



print(f"test: {tensor_data}")