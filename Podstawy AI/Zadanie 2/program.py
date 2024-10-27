import numpy
import keras
from keras import layers

def main():
    (x_train, y_train) = load_data("MNIST_ORG/train-images-idx3-ubyte",
                                   "MNIST_ORG/train-labels-idx1-ubyte",
                                   60000)
    (x_test, y_test) = load_data("MNIST_ORG/t10k-images-idx3-ubyte",
                                 "MNIST_ORG/t10k-labels-idx1-ubyte",
                                 10000)
    
    # building the model
    y_train = keras.utils.to_categorical(y_train, 10)
    y_test  = keras.utils.to_categorical(y_test, 10)
    
    model = keras.Sequential(
        [
        keras.Input(shape=(28,28,1)),
        layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Flatten(),
        layers.Dropout(0.5),
        layers.Dense(10, activation="softmax"),
    ]
    )
    
    model.summary()
    
    #training the model
    batch_size = 128
    epochs = 15

    model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])
    model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1)

    # score
    score = model.evaluate(x_test, y_test, verbose=0)
    print("Test loss:", score[0])
    print("Test accuracy:", score[1])



def load_data(images_filename, labels_filename, images_number = 5):
    train_image_file = open(images_filename, "rb")
    train_label_file  = open(labels_filename, "rb")
    image_size = 28

    # prepare images
    train_image_file.read(16)   #skip meta info
    buf = train_image_file.read(image_size * image_size * images_number)
    train_images = numpy.frombuffer(buf, dtype=numpy.uint8).astype(numpy.float32) / 255
        # by dividing by 255 we normalize the image as the pixels
        # become values from 0 to 1
    train_images = train_images.reshape(images_number, image_size, image_size, 1)

    # read the labels
    train_label_file.read(8)
    buf = train_label_file.read(1 * images_number)
    train_labels = numpy.frombuffer(buf,dtype=numpy.uint8)
    
    return (train_images, train_labels)

if __name__ == "__main__":
    main()