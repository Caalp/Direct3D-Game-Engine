import math
import random

def check(E):
    """[summary]
        Check list of errors if all zero means no error return True else False
    Args:
        E ([list]): [list of error values from one iteration of inputs]

    Returns:
        [bool]: [Whether error list has error or not if all true return True else False]
    """
    for e in E:
        if (e != 0):
            return False
    return True

def StepFunc(var,t = 0):
    for i in range(0,len(var)):
        if (var[i] >= t):
            var[i] = 1
        else:
            var[i] = 0

def Update(inputs,inputs_h,weights_hi,weights_ho,err):
    """[summary]
        Update weights here between input and hidden layer , and between hidden layer and output
    Args:
        inputs ([string]): [input to the network]
        inputs_h ([list]): [outputs of the perceptrons from hidden layer]
        weights_hi ([list]): [weights from input layer to hidden layer]
        weights_ho ([list]): [weights from hidden layer to output]
        err ([int]): [correct output - guessed output]

    Returns:
        [type]: [description]
    """
    updated_weights = []
    alpha = 0.02
    
    for i in range(0,len(weights_hi)):
        updated_weights.append(float(weights_hi[i]) + (alpha*float(inputs[i % (len(inputs))]) * err))

    for j in range(0,len(weights_ho)):
        updated_weights.append(float(weights_ho[j]) + (alpha*float(inputs_h[j % (len(inputs_h))]) * err))

    return updated_weights

def randomize(w,size):
    """[summary]
        Create list with given size whose elements are created randomly
    Args:
        w ([list]): [description]
        size ([int]): [description]
    """
    for _ in range(size):
        w.append(random.uniform(-2,2))

def calculate(inputs,weights,bias):
    """[summary]
        Calculate output of the newtork for given inputs, weights and bias
    Args:
        inputs ([string]): [inputs]
        weights ([list]): [weights]
        bias ([list]): [bias for the layer]

    Returns:
        [list]: [output of each perceptron]
    """
    outputs = []
    result = 0
    j = 0
    for i in range(0,len(weights)):
        if (j < len(inputs)):
            #a = i%len(weights)
            result += float(inputs[j])*weights[i]
            j += 1
            if (j ==len(inputs)):
                result += bias[int(i / len(bias)%len(bias))]
                outputs.append(result)
                j = 0
                result = 0
    return outputs

def test_feed_forward(inputs,weights_in,weights_out,bias_in,bias_out):
    """[summary]
        Run feed-forward network with giben inputs and weights
    Args:
        inputs ([string]): [input to the network]
        weights_in ([list]): [weights between input and hidden layer]
        weights_out ([list]): [weights between hidden layer and output]
        bias_in ([list]): [bias between input layer and hidden layer]
        bias_out ([list]): [bias to the output]

    Returns:
        [int]: [output of the network]
    """
    output_h = calculate(inputs,weights_in,bias_in)
    StepFunc(output_h)
    output_o = calculate(output_h,weights_out,bias_out)
    StepFunc(output_o)
    return output_o

if __name__ == "__main__":

    i = 0
    it = 0
    line_count = 0

    E = []
    weights_in = []
    inp_l = []
    bias = []
    weights_out = []
    inp_temp = []

    randomize(weights_in,9) 
    randomize(weights_out,3)
    randomize(bias,4)
        
    with open("./test.txt",'r') as file:
        for line in file:
            inp_l.append(line)
            line_count +=1
    
    while(True):
        
        ## Do Testing here after I found the value 
        ## Here I put the values manually and test if values are actually correct

        # for inpr in inp_l:
        #     w_in = [-4.195691792629852, -0.35497744833956, -0.3240524854587411, -1.9190984291712119, 2.852093873194121, -1.0558728606220356, -1.5410816959836466, 2.5131585605816475, -2.0997530353167373]
        #     w_out = [1.1914735482050836, -0.00677757310173472, 1.179871107494156]
        #     bias_in = [0.3692792593872811, -0.20073690787406528, 1.1634206497606834]
        #     bias_out = [-1.17874732531308]
        #     print(inpr[:3] +  ": " + str(test_feed_forward(inpr[:3],w_in,w_out,bias_in,bias_out)))
        

        ## Outputs from hidden layer
        inp = random.choice(inp_l)
        if (inp not in inp_temp):
            inp_temp.append(inp)
        else:
            while(inp in inp_temp):
                inp = random.choice(inp_l)
                if (inp not in inp_temp):
                    inp_temp.append(inp)
                    break
            
        outputs_ho = calculate(inp[:3],weights_in,bias)
        StepFunc(outputs_ho)
        
        ## Feed outputs to the output layer
        output_o = calculate(outputs_ho,weights_out,[bias[-1]])
        StepFunc(output_o)

        ## Find error 
        error = float(inp[len(inp)-2])-output_o[0]

        ## Adjust/Update weights here
        updated_weights = Update(inp[:3],outputs_ho,weights_in,weights_out,error)
        weights_in = updated_weights [:len(weights_in)]
        weights_out = updated_weights[len(weights_in):]
        E.append(error)

        i += 1
        if (i == line_count):
            r = check(E)
            if(not r):
                E.clear()
                inp_temp.clear()
            else:
                print(inp_temp)
                print("W11: {}, W12: {}, W13: {}".format(weights_in[0],weights_in[1],weights_in[2]))
                print("W21: {}, W22: {}, W23: {}".format(weights_in[3],weights_in[4],weights_in[5]))
                print("W31: {}, W32: {}, W33: {}".format(weights_in[6],weights_in[7],weights_in[8]))
                print("Wh1: {}, Wh2: {}, Wh3: {}".format(weights_out[0],weights_out[1],weights_out[2]))
                print("b0: {}, b1: {}, b2: {}".format(bias[0],bias[1],bias[2]))
                print("b3: {}".format(bias[3]))
                break
            if (it > 80000):
                ## Reset weight and bias and start all over again
                weights_in.clear()
                bias.clear()
                weights_out.clear()
                randomize(weights_in,9)
                randomize(bias,4)
                randomize(weights_out,3)
                it = 0

            i = 0
        it += 1
        
       


