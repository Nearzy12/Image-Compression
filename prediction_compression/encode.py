# CALIC Prediction encrypting 

# Set variables for surrounding pixels 


s_0 = -1
s_1 = -1
T = 0


prediction = 0
error = 0

T = 0

# Create a dictionary with directions as keys and values
directions = {'NN': 124, 'NNE': 123, 'NW': 124, 'N': 124, 'NE': 124, 'WW': 124, 'W': 126}
pixel_being_predicted = 123

# Loop through the array of tuples
# for direction, value in directions.items():
#    print(f"{direction}: {value}")

# Set values for s_0 and s_1 and then find T
s_0 = directions['W']

# Find s_1
for direction, value in directions.items():
    if(value != s_0):
        s_1 = value

# Now see if there is a third value
for direction, value in directions.items():
    if(value != s_0 and value != s_1):
        # Escape signal
        T = 2

# T = 0
if(pixel_being_predicted == s_0 and T != 2):
    T = 0
    prediction = directions['W']

# T = 1
elif(pixel_being_predicted == s_1 and T != 2):
    T = 1
    prediction = directions['N']

else:
    T = 2

# Now we are in continuous mode 
    d_h = 0.0
    d_v = 0.0

    NNE = directions['NNE']
    WW = directions['WW']
    NW = directions['NW']
    NN = directions['NN']
    NE = directions['NE']
    N = directions['N']
    W = directions['W']

    w_ww = abs(W - WW)
    n_nw = abs(N - NW)
    ne_n = abs(NE - N)

    w_nw = abs(W - NW)
    n_nn = abs(N - NN)
    ne_nne = abs(NE - NNE)

    d_h = w_ww + n_nw + ne_n
    d_v = w_nw + n_nn + ne_nne

    print(f"dh:{d_h} dv:{d_v}")
    print(f"dv-dh = {d_v - d_h}")
    print(f"dh-dv = {d_h - d_v}")

    # Now using d_h and d_v the GAP value is computed

    if(d_v - d_h > 80):
        # Sharp horizontal edge
        print("Sharp horizontal edge")
        prediction = W
    else:
        if(d_h - d_v > 80):
            # Sharp vertical edge
            print("Sharp vertical edge")
            prediction = N
        else:
            prediction = ((W + N)/2) + ((NE - NW)/4)
            if(d_v - d_h > 32):
                # Horizontal edge
                print("Horizontal edge")
                prediction = (prediction * 0.5) + (W * 0.5)
            else:
                if(d_h - d_v > 32):
                    # Vertical edge
                    print("Vertical edge")
                    prediction = (prediction * 0.5) + (N * 0.5)
                else:
                    if(d_v - d_h > 8):
                        # Weak horizontal edge
                        print("Weak horizontal edge")
                        prediction = (prediction * 0.75) + (W * 0.25)
                    else:
                        if(d_h - d_v > 8):
                            print("")
                            # Weak vertical edge 
                            print("Weak vertical edge")
                            prediction = (prediction * 0.75) + (N * 0.25)

error = pixel_being_predicted - prediction
print(f"T value:{T} Prediction value: {prediction} error:{error}")   





