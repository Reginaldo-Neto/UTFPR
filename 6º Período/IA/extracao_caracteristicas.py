import os
import numpy as np
import argparse as ap
from PIL import Image

parser = ap.ArgumentParser(description='Process some integers.')
parser.add_argument('--root_dir', type=str, required=True,
                    help='the root directory where images are stored')
parser.add_argument('--num_quadrants', type=int, required=True,
                    help='the number of quadrants to divide the images into')
parser.add_argument('--output_file_prefix', type=str, required=True,
                    help='treino ou teste')

args = parser.parse_args()

# Now you can access the arguments using `args.root_dir` and `args.num_quadrants`
root_dir = args.root_dir
num_quadrants = args.num_quadrants
prefix = args.output_file_prefix

output_name = prefix + str(num_quadrants) + "x" + str(num_quadrants) + ".txt"
if os.path.exists(output_name):
    os.remove(output_name)

# Define the root directory where the images are stored

# Initialize the table to store the results
table = np.zeros((0, num_quadrants*num_quadrants*2+1))

# Loop through each folder in the root directory
for folder in os.listdir(root_dir):
    folder_path = os.path.join(root_dir, folder)
    
    # Loop through each file in the folder
    for filename in os.listdir(folder_path):
        
        cur_class = folder_path[-1]
        
        if filename.endswith(".bmp"):
            # Construct the full path of the image
            img_path = os.path.join(folder_path, filename)
            
            # Open the image using PIL
            img = Image.open(img_path)

            w, h = img.size

            q_w = w // num_quadrants
            q_h = h // num_quadrants

            # Initialize the list to store the counts of black and white pixels in each quadrant
            counts = []
            
            for i in range(num_quadrants):
                for j in range(num_quadrants):

                    x1 = i * q_h
                    y1 = j * q_w
                    x2 = x1 + q_h
                    y2 = y1 + q_w

                    quadrant = img.crop((x1, y1, x2, y2))

                    black = quadrant.histogram()[0]
                    white = quadrant.histogram()[255]

                    counts.append(black)
                    counts.append(white)

            # Append the class label to the end of the counts list
            counts.append(cur_class)

            # Append the counts to the table using numpy.vstack()
            row = np.array(counts).reshape(1, -1)
            table = np.vstack([table, row])

            # Close the image
            img.close()

# Calculate the mean and standard deviation of each column
means = np.mean(table[:, :-1].astype(float), axis=0)
stds = np.std(table[:, :-1].astype(float), axis=0)

# Normalize the counts using zscore
table[:, :-1] = (table[:, :-1].astype(float) - means) / stds

# Save the table to a file
table = table.astype('float64')
# Create the header string with commas between columns
header = ",".join(["black" + str(i//2+1) if i%2==0 else "white" + str(i//2+1) for i in range(num_quadrants*num_quadrants*2)])
header += ",class\n"  # Add the class column

# Open the file in append mode ('a')
with open(output_name, 'a') as f:
    f.write(header)  # Write the header string to the file

# Append the table to the file without the header
with open(output_name, 'a') as f:
    np.savetxt(f, table, delimiter=",", fmt="%0.10f," * (num_quadrants * num_quadrants * 2) + "%d", newline='\n')


# Append the table to the file without the header
with open(output_name, 'a') as f:
    np.savetxt(f, table, delimiter=",", fmt="%0.10f," * (num_quadrants * num_quadrants * 2) + "%d", newline='\n')
