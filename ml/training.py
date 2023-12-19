import time
import cv2
from sklearn import svm
import os
from PIL import Image
from skimage.feature import hog

x: list[int | float] = []
y: list[str] = []

cell_per_block = (1, 1)
pixels_per_cell = (8, 8)
window_size = 8


def read_blobs():
    plants = []
    pots = []
    for filename in os.listdir("../dataset/blobs/plants"):
        file_path = os.path.join("../dataset/blobs/plants", filename)
        plants.append(file_path)
    for filename in os.listdir("../dataset/blobs/pots"):
        file_path = os.path.join("../dataset/blobs/pots", filename)
        pots.append(file_path)
    return (plants, pots)


def get_data():
    plants = []
    pots = []
    random = []
    for filename in os.listdir("data/plant"):
        file_path = os.path.join("data/plant", filename)
        plants.append(file_path)
    for filename in os.listdir("data/pot"):
        file_path = os.path.join("data/pot", filename)
        pots.append(file_path)
    for filename in os.listdir("data/random"):
        file_path = os.path.join("data/random", filename)
        random.append(file_path)
    return (plants, pots, random)


def normalize_data():
    plants, pots, random = get_data()
    for index, url in enumerate(plants):
        img = Image.open(url)
        if img.height == 32:
            img.close()
            continue
        img = img.resize((32, 32))
        img.save(f"data/plant/{index}.jpg")
    for index, url in enumerate(pots):
        img = Image.open(url)
        if img.height == 32:
            img.close()
            continue
        img = img.resize((32, 32))
        img.save(f"data/pot/{index}.jpg")
    for index, url in enumerate(random):
        img = Image.open(url)
        if img.height == 32:
            img.close()
            continue
        img = img.resize((32, 32))
        img = img.convert("RGB")
        img.save(f"data/random/{index}.jpg")


def create_dataframe():
    global x, y
    plants, pots, random = get_data()
    for url in plants:
        img = Image.open(url)
        fd = hog(
            img,
            orientations=8,
            pixels_per_cell=pixels_per_cell,
            cells_per_block=cell_per_block,
            visualize=True,
            channel_axis=-1,
        )
        x.append(fd[0])
        y.append("plant")
    for url in pots:
        img = Image.open(url)
        fd = hog(
            img,
            orientations=8,
            pixels_per_cell=pixels_per_cell,
            cells_per_block=cell_per_block,
            visualize=True,
            channel_axis=-1,
        )
        x.append(fd[0])
        y.append("pot")
    for url in random:
        img = Image.open(url)
        fd = hog(
            img,
            orientations=8,
            pixels_per_cell=pixels_per_cell,
            cells_per_block=cell_per_block,
            visualize=True,
            channel_axis=-1,
        )
        x.append(fd[0])
        y.append("object")


normalize_data()
create_dataframe()
clf = svm.SVC(decision_function_shape="ovo", kernel="rbf", C=200, probability=True)
clf.fit(x, y)  # type:ignore
# with open("model.pkl", "rb") as f:
#     clf: svm.SVC = pickle.load(f)
img = Image.open("test/4.jpg")
imgcv = cv2.imread("test/4.jpg")

now = time.time()

xa = 0
ya = 0


def get_value(x: list):
    plant = x[0][0]
    pot = x[0][1]
    obj = x[0][2]
    if plant > pot and plant > obj:
        if plant > 85.0:
            return "plant"
    if pot > plant and pot > obj:
        if pot > 85.0:
            return "pot"
    if obj > plant and obj > pot:
        if obj > 85.0:
            return "object"
    return None


while xa < 64:
    while ya < 64:
        window = img.crop((xa, ya, xa + window_size, ya + window_size))
        window = window.resize((32, 32))
        fd = hog(
            window,
            orientations=8,
            pixels_per_cell=pixels_per_cell,
            cells_per_block=cell_per_block,
            visualize=True,
            channel_axis=-1,
        )
        res = clf.predict_proba([fd[0]])  # type:ignore
        if get_value(res) == "plant":  # type:ignore
            print(res)
            cv2.rectangle(
                imgcv, (xa, ya), (xa + window_size, ya + window_size), (255, 0, 0), 1
            )
            ya += window_size
            xa += window_size
            continue
            # print(f"{xa}:{ya} = {res[0]}")
        ya += 1
    xa += 1
    ya = 0
print(f"time elapsed : { (time.time() - now) *1000 } ms")

cv2.imshow("image", imgcv)
cv2.waitKey(0)


# # save model
# with open("model.pkl", "wb") as f:
#     pickle.dump(clf, f)
