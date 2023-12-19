from sklearn import svm
import os
from PIL import Image
from skimage.feature import hog
from skimage import exposure
import pickle

x: list[int | float] = []
y: list[str] = []


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
    for filename in os.listdir("data/plant"):
        file_path = os.path.join("data/plant", filename)
        plants.append(file_path)
    for filename in os.listdir("data/pot"):
        file_path = os.path.join("data/pot", filename)
        pots.append(file_path)
    return (plants, pots)


def normalize_data():
    plants, pots = read_blobs()
    for index, url in enumerate(plants):
        img = Image.open(url)
        img = img.resize((64, 64))
        img.save(f"data/plant/{index}.jpg")
    for index, url in enumerate(pots):
        img = Image.open(url)
        img = img.resize((64, 64))
        img.save(f"data/pot/{index}.jpg")


def create_dataframe():
    global x, y
    plants, pots = get_data()
    for index, url in enumerate(plants):
        img = Image.open(url)
        fd = hog(
            img,
            orientations=8,
            pixels_per_cell=(16, 16),
            cells_per_block=(1, 1),
            visualize=True,
            channel_axis=-1,
        )
        x.append(fd[0])
        y.append("plant")
    for index, url in enumerate(pots):
        img = Image.open(url)
        fd = hog(
            img,
            orientations=8,
            pixels_per_cell=(16, 16),
            cells_per_block=(1, 1),
            visualize=True,
            channel_axis=-1,
        )
        x.append(fd[0])
        y.append("pot")


create_dataframe()
clf = svm.SVC()
clf.fit(x, y)

img = Image.open("../dataset/blobs/pots/50.pot.jpg")
img = img.resize((64, 64))
fd = hog(
    img,
    orientations=8,
    pixels_per_cell=(16, 16),
    cells_per_block=(1, 1),
    visualize=True,
    channel_axis=-1,
)


res = clf.predict([fd[0]])
print(res)


# save model
with open("model.pkl", "wb") as f:
    pickle.dump(clf, f)
