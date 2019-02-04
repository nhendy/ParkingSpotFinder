import torch
from mobilenetV1_ssd import create_mobilenetv1_ssd
import copy
from parse import CustomDetection, get_anno_dataset, get_anno_per_image
import torch.utils.data as data
from torchvision import transforms as T
# segment_root = "C:/Users/Damini/Documents/PKLot/PKLotSegmented/PUC/Cloudy/2012-09-28"
# xml_root = "C:/Users/Damini/Documents/PKLot/PKLot/PUCPR/Cloudy/2012-09-16"

xml_root = "/Users/programming/PycharmProjects/Park/park_3/data"
CLASSES = 2

model = create_mobilenetv1_ssd(21, True)
ssd_net, _, _= build_ssd(args, num_classes=CLASSES)
# model.load_state_dict(torch.load("mobilenet-v1-ssd-mp-0_675.pth"), strict=False)

#use GOU
# device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

if torch.cuda.is_available():
    torch.set_default_tensor_type('torch.cuda.FloatTensor')


def train(model = None, criterion = None, optim = None, scheduler=None, data=None, epochs=25, phase='train', loader=None):

        # model_weights = copy.deepcopy(model.load_state_dict(torch.load("mobilenet-v1-ssd-mp-0_675.pth"), strict=False))
        best_acc = 0.0
        for epoch in range(epochs):
            if phase == 'Train':
                scheduler.step()
                model.train()
            running_loss = 0.0
            correct_predict = 0
            print(len(loader))
            input, label  = next(iter(loader))
            print(input)
            print(input.size())
                # inputs = inputs.to(device)
                # labels = labels.to(device)
                #
                # print(inputs)
                # print(labels)
            output = model(input.float())
            print("what")cd

if __name__=='__main__':
    transform = T.Compose([
        T.RandomSizedCrop(224),
        T.RandomHorizontalFlip,
        T.ToTensor(),
        T.Normalize(mean=[0.485, 0.456, 0.406],
                    std=[0.229, 0.224, 0.225])
    ])
    annos = get_anno_dataset(xml_root)
    dataset = CustomDetection(root = xml_root, annotation=annos, phase="Train")

    train_loader = data.DataLoader(dataset=dataset, batch_size=4, num_workers=4, shuffle = False)
    train(model=model, loader=train_loader)

    print(len(train_loader))


    # print(dataset[0])

    # print(len(train_loader))



