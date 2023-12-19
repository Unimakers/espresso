from PIL import Image
from ultralytics import YOLO
import os
import matplotlib.pyplot as plt

from skimage.feature import hog
from skimage import exposure
import csv

model = YOLO("yolov8n.pt")

# vase:75 plant: 58 CUP: 41, bowl: 45,
labels = {58: "plant", 45: "pot", 41: "pot", 75: "pot"}


def read_dataset():
    files = []
    for filename in os.listdir("../dataset/raw"):
        file_path = os.path.join("../dataset/raw", filename)
        files.append(file_path)
    return files


def read_blobs():
    files = []
    for filename in os.listdir("../dataset/blobs/plants"):
        file_path = os.path.join("../dataset/blobs/plants", filename)
        files.append(file_path)
    return files


def hog_test():
    dataset = read_blobs()
    image = Image.open(dataset[0])
    image = image.resize((64, 64))
    fd, hog_image = hog(
        image,
        orientations=8,
        pixels_per_cell=(16, 16),
        cells_per_block=(1, 1),
        visualize=True,
        channel_axis=-1,
    )
    print(len(fd))
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4), sharex=True, sharey=True)

    ax1.axis("off")
    ax1.imshow(image, cmap=plt.cm.gray)  # type: ignore
    ax1.set_title("Input image")

    # Rescale histogram for better display
    hog_image_rescaled = exposure.rescale_intensity(hog_image, in_range=(0, 10))  # type: ignore

    ax2.axis("off")
    ax2.imshow(hog_image_rescaled, cmap=plt.cm.gray)  # type: ignore
    ax2.set_title("Histogram of Oriented Gradients")
    plt.show()


def extract_labels():
    dataset = read_dataset()
    results = model(dataset)
    count = 0
    for r in results:
        if len(r.boxes) == 0:
            continue
        for box in r.boxes:
            label = labels.get(box.cls.item())
            if label is not None:
                box = box.xyxy.tolist()
                x0 = box[0][0]
                y0 = box[0][1]
                x1 = box[0][2]
                y1 = box[0][3]
                im = Image.open(r.path)
                im = im.crop((x0, y0, x1, y1))
                match label:
                    case "pot":
                        im.save(f"../dataset/blobs/pots/{count}.pot.jpg")
                        count += 1
                    case "plant":
                        im.save(f"../dataset/blobs/plants/{count}.plant.jpg")
                        count += 1
                im.close()


def resize_dataset():
    count = 0
    for file in read_dataset():
        img = Image.open(file)
        img = img.resize((512, 512))
        img = img.rotate(-90)
        img.save(f"../dataset/{count}_raw.jpg")
        count += 1


# extract_labels()
hog_test()
