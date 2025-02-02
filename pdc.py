import argparse
import cv2
import numpy as np
import os

parser = argparse.ArgumentParser(description='Génération d\'un modèle de point de croix à partir d\'une image')
parser.add_argument('modele', metavar='FILE', type=str, help='nom du modele')
parser.add_argument('dim', metavar='SIDE', type=str, help='cote du redimentionnement', choices=('X', 'Y'))
parser.add_argument('valdim', metavar='SIZE', type=int, help='taille du fichier de sortie')

args = parser.parse_args()

path_file = args.modele
new_dim = args.valdim

# Test if the file exist
if not os.path.exists(path_file):
    print('ERROR: Le fichier \'{}\' n\'existe pas'.format(path_file))
    exit(1)

# Get dimensions of the file
im = cv2.imread(path_file)
print(im.shape)

orig_Y_dim = im.shape[0]
orig_X_dim = im.shape[1]
orig_ratio = orig_Y_dim/orig_X_dim

print('Old X = {}'.format(orig_X_dim))
print('Old Y = {}'.format(orig_Y_dim))

# Test the new Y dimension
if (args.dim == 'X'):
    if (new_dim <= 0) or (new_dim > orig_X_dim):
        print('ERROR: La dimension {} n\'est pas correcte (0 < SIZE <= {})'.format(new_dim, orig_X_dim))
        exit(1)
else:
    if (new_dim <= 0) or (new_dim > orig_Y_dim):
        print('ERROR: La dimension {} n\'est pas correcte (0 < SIZE <= {})'.format(new_dim, orig_Y_dim))
        exit(1)


# Filter image
linear_filter = cv2.boxFilter(im, -1, (3, 3))
blur = cv2.blur(im, (3, 3))
gaussian = cv2.GaussianBlur(im, (3, 3), 0)


## Resize l'image
# Calculate new resized images dimensions
if (args.dim == 'X'):
    new_x_dim = new_dim
    new_y_dim = int(round(orig_ratio * new_dim, 0))
else:
    new_x_dim = int(round((1/orig_ratio) * new_dim, 0))
    new_y_dim = new_dim

print('New X = {}'.format(new_x_dim))
print('New Y = {}'.format(new_y_dim))

im_resized0 = cv2.resize(gaussian,
                        dsize=(new_x_dim, new_y_dim),
                        interpolation=cv2.INTER_NEAREST)



## Quantization of color
K = 10
Z = im_resized0.reshape((-1,3))

# convert to np.float32
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
Z = np.float32(Z)
ret,label,center=cv2.kmeans(Z,K,None,criteria,10,cv2.KMEANS_RANDOM_CENTERS)

center = np.uint8(center)
res = center[label.flatten()]
res2 = res.reshape((im_resized0.shape))

## Extract all colors
print(res2.shape)
colors = np.unique(res2.reshape(-1, 3), axis=0)
print(colors)

## Associate a symbol to each color
symb = 65
colors_table =  []
for color in colors:
    colors_table += [[color, chr(symb)]]
    print(chr(symb))
    symb = symb + 1

print(colors_table)

## Generate an array with the symbole remplacement
print("hzefhzehfh")
print(res2.shape[0])
print(res2.shape[1])
dim = (res2.shape[0], res2.shape[1])
print(dim)
char_res = np.empty(dim, dtype=str)
print(char_res.shape)
print(char_res.shape)
for color in colors_table:
    for y in range(0, new_y_dim):
        for x in range(0, new_x_dim):
            # print("x={}, y={}, pix={},c={}".format(x, y, res2[y][x], color[0]))
            if np.array_equal(res2[y][x], color[0]):
                char_res[y][x] = color[1]

print(char_res)
print(char_res.shape)
                
## Generate the csv
cv2.namedWindow("output0", cv2.WINDOW_NORMAL)
cv2.resizeWindow("output0", new_x_dim, new_y_dim)
cv2.namedWindow("output1", cv2.WINDOW_NORMAL)
cv2.resizeWindow("output1", orig_X_dim, orig_Y_dim)
cv2.imshow("output0", res2)
cv2.imshow("output1", gaussian)
cv2.waitKey(0)
cv2.imwrite('output.jpg', res2)
np.savetxt("foo.csv", char_res, delimiter=",", fmt='%s')

