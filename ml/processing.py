from PIL import Image
from ultralytics import YOLO
import os
import numpy as np

model = YOLO("yolov8n.pt")

# vase:75 plant: 58 CUP: 41, bowl: 45,
labels = {58: "plant", 45: "pot", 41: "pot", 75: "pot"}


def read_dataset():
    files = []
    for filename in os.listdir("../dataset/raw"):
        file_path = os.path.join("../dataset/raw", filename)
        files.append(file_path)
    return files


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
                        im.save(f"../dataset/blobs/{count}.pot.jpg")
                        count += 1
                    case "plant":
                        im.save(f"../dataset/blobs/{count}.plant.jpg")
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
