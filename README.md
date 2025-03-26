# Project Overview:
Our project aims to create an imaginary train using the C language and
pointers, a feature of this language, and complete tasks such as adding and
removing wagons, creating materials, adding and removing materials to
wagons within certain rules. All this information is retrieved from a text file
when the script is initialized and the changes are saved in the same way.

# Project Structure:
Our project consist of 14 file:

main.c: Where we invoke our all functions.

train.h, train.c: We defined all struct type here. (MaterialType,
LoadedMaterial, Wagon, Train). And here, there function for initalizing train,
freeing train, and displaying train status.

vagon.h, vagon.c: We defined functions for creating wagon, adding wagon
to train, loading material to specific wagon and loading material to wagon
starting from first wagon.

material.h, material.c: We defined functions for displaying material status,
removing materail node, finding material in wagon, unloading material and
unloading material from specific wagon.

file_ops.h, file_ops.c: We defined functions for getting last material, getting
boxes infos from text file, loading train status from file and saving file to text
file.

utils.h, utils.c: We defined functions for printing menu interface and
material status.

Makefile

main.exe

train_status.txt

# Console Outputs
![Ekran görüntüsü 2025-01-13 194632](https://github.com/user-attachments/assets/3bafb569-58b4-4210-b199-6c89129f5367)

![Ekran görüntüsü 2025-01-13 194704](https://github.com/user-attachments/assets/a51fd662-3d80-46d4-8938-3fc85c512f46)

![Ekran görüntüsü 2025-01-13 194725](https://github.com/user-attachments/assets/861781bc-9112-4daf-b834-7e613121aa14)

![Ekran görüntüsü 2025-01-13 194740](https://github.com/user-attachments/assets/bb812254-f8b6-48cf-9657-ccdddf04909a)

![Ekran görüntüsü 2025-01-13 194857](https://github.com/user-attachments/assets/7aba8c15-8236-4be4-813f-370e03fb06ae)

![Ekran görüntüsü 2025-01-13 194912](https://github.com/user-attachments/assets/58dfc3dd-49eb-4b25-bd1c-4806b3f565a3)

![Ekran görüntüsü 2025-01-13 195017](https://github.com/user-attachments/assets/c6d97928-0478-42e7-bbd1-71d050fbfd1f)

![Ekran görüntüsü 2025-01-13 195050](https://github.com/user-attachments/assets/64535647-7a2a-4479-b850-8fa33cf8ae39)

![Ekran görüntüsü 2025-01-13 195105](https://github.com/user-attachments/assets/32b847d4-26b0-44f8-ae1d-27faccb32b09)

![Ekran görüntüsü 2025-01-13 195132](https://github.com/user-attachments/assets/5414c008-4a49-4c7b-a642-617421d5c0ce)

![Ekran görüntüsü 2025-01-13 195210](https://github.com/user-attachments/assets/6e834d5a-2325-47af-81cf-4491d0528960)

![Ekran görüntüsü 2025-01-13 195330](https://github.com/user-attachments/assets/00d7a1ad-0011-4b77-96a5-790fd51054e9)

![Ekran görüntüsü 2025-01-13 195337](https://github.com/user-attachments/assets/a0dca6d7-d71b-4b0b-a140-497fdc7b0b51)

![Ekran görüntüsü 2025-01-13 195359](https://github.com/user-attachments/assets/3bab1ad7-c39c-4c0a-b138-3a8746d7abd5)

![Ekran görüntüsü 2025-01-13 195413](https://github.com/user-attachments/assets/0ab9916e-7a4f-416a-8ce6-0e4e0ad5fc7d)

# Our text file (train_status.txt):
![Ekran görüntüsü 2025-01-13 195430](https://github.com/user-attachments/assets/201bf33e-351d-4b25-8496-31f8be5be648)















