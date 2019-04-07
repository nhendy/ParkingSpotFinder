def VGG_16():
    '''Model definition'''

    model = Sequential()
    model.add(Conv2D(64, (11, 11,), padding='valid', strides=(4,4), input_shape=(img_height,img_width,num_channels), name='conv1'))
    model.add(Activation('relu', name='relu1'))
    model.add(LocalResponseNormalization(name='norm1'))
    model.add(MaxPooling2D((2,2), padding='same', name='pool1'))

    model.add(Conv2D(256, (5,5), padding='same', name='conv2'))
    model.add(Activation('relu', name='relu2'))
    model.add(LocalResponseNormalization(name='norm2'))
    model.add(MaxPooling2D((2,2), padding='same', name='pool2'))

    model.add(Conv2D(256, (3, 3), padding='same', name='conv3'))
    model.add(Activation('relu', name='relu3'))
    model.add(Conv2D(256, (3, 3), padding='same', name='conv4'))
    model.add(Activation('relu', name='relu4'))
    model.add(Conv2D(256, (3, 3), padding='same', name='conv5'))
    model.add(Activation('relu', name='relu5'))
    model.add(MaxPooling2D((2,2), padding='same', name='pool5'))

    return model