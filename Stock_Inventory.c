#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "products.txt"

struct Product
{
	int id;
	char name[50];
	int quantity;
	float buyPrice;
	float sellPrice;
};

struct Product products[MAX];
int count = 0;

// Function Prototypes
void loadData();
void saveData();
void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void purchaseStock();
void sellStock();
int login();
int generateID();

int login_admn()
{
	char admin[20], admin_pass[20];
	printf("=== Admin Login ===\n");
	printf("Username: ");
	scanf("%s", admin);
	printf("Password: ");
	scanf("%s", admin_pass);

	if (strcmp(admin, "admin") == 0 && strcmp(admin_pass, "admin123") == 0)
	{
		printf("Login Successful!\n");
		return 1;
	}
	return 0;
}

int login_customer()
{
	char customer[20], customer_pass[20];
	printf("=== Customer Login ===\n");
	printf("customer_name: ");
	scanf("%s", customer);
	printf("Password: ");
	scanf("%s", customer_pass);

	if (strcmp(customer, "customer") == 0 && strcmp(customer_pass, "customer123") == 0)
	{
		printf("Login Successful!\n");
		return 1;
	}
	return 0;
}

void loadData()
{
	FILE *fp = fopen(FILE_NAME, "r");
	if (!fp)
		return;

	while (fscanf(fp, "%d %s %d %f %f",
				  &products[count].id,
				  products[count].name,
				  &products[count].quantity,
				  &products[count].buyPrice,
				  &products[count].sellPrice) == 5)
	{
		count++;
	}
	fclose(fp);
}

void saveData()
{
	FILE *fp = fopen(FILE_NAME, "w");
	for (int i = 0; i < count; i++)
	{
		fprintf(fp, "%d %s %d %.2f %.2f\n",
				products[i].id,
				products[i].name,
				products[i].quantity,
				products[i].buyPrice,
				products[i].sellPrice);
	}
	fclose(fp);
}

int generateID()
{
	if (count == 0)
		return 1;
	return products[count - 1].id + 1;
}

void addProduct()
{
	struct Product p;
	p.id = generateID();

	printf("Enter product name: ");
	scanf("%s", p.name);
	printf("Enter quantity: ");
	scanf("%d", &p.quantity);
	printf("Enter buying price: ");
	scanf("%f", &p.buyPrice);
	printf("Enter selling price: ");
	scanf("%f", &p.sellPrice);

	products[count++] = p;

	printf("Product added successfully!\n");
}

void viewProducts()
{
	if (count == 0)
	{
		printf("No products found.\n");
		return;
	}

	printf("\nID\tName\tQty\tBuy\tSell\n");
	for (int i = 0; i < count; i++)
	{
		printf("%d\t%s\t%d\t%.2f\t%.2f\n",
			   products[i].id,
			   products[i].name,
			   products[i].quantity,
			   products[i].buyPrice,
			   products[i].sellPrice);
	}
}

void searchProduct()
{
	int id;
	printf("Enter product ID to search: ");
	scanf("%d", &id);

	for (int i = 0; i < count; i++)
	{
		if (products[i].id == id)
		{
			printf("Found: %d %s %d %.2f %.2f\n",
				   products[i].id,
				   products[i].name,
				   products[i].quantity,
				   products[i].buyPrice,
				   products[i].sellPrice);
			return;
		}
	}
	printf("Product not found.\n");
}

void updateProduct()
{
	int id;
	printf("Enter product ID to update: ");
	scanf("%d", &id);

	for (int i = 0; i < count; i++)
	{
		if (products[i].id == id)
		{
			printf("New name: ");
			scanf("%s", products[i].name);
			printf("New quantity: ");
			scanf("%d", &products[i].quantity);
			printf("New buy price: ");
			scanf("%f", &products[i].buyPrice);
			printf("New sell price: ");
			scanf("%f", &products[i].sellPrice);

			printf("Product updated.\n");
			return;
		}
	}
	printf("Product not found.\n");
}

void deleteProduct()
{
	int id;
	printf("Enter product ID to delete: ");
	scanf("%d", &id);

	for (int i = 0; i < count; i++)
	{
		if (products[i].id == id)
		{
			for (int j = i; j < count - 1; j++)
				products[j] = products[j + 1];
			count--;
			printf("Product deleted.\n");
			return;
		}
	}
	printf("Product not found.\n");
}

void purchaseStock()
{
	int id, qty;
	printf("Enter product ID to purchase: ");
	scanf("%d", &id);

	for (int i = 0; i < count; i++)
	{
		if (products[i].id == id)
		{
			printf("Enter quantity to add: ");
			scanf("%d", &qty);
			products[i].quantity += qty;
			printf("Stock updated!\n");
			return;
		}
	}
	printf("Product not found.\n");
}

void sellStock()
{
	int id, qty;
	printf("Enter product ID to sell: ");
	scanf("%d", &id);

	for (int i = 0; i < count; i++)
	{
		if (products[i].id == id)
		{
			printf("Enter quantity to sell: ");
			scanf("%d", &qty);

			if (qty > products[i].quantity)
			{
				printf("Not enough stock!\n");
			}
			else
			{
				products[i].quantity -= qty;
				printf("Sale successful!\n");
			}
			return;
		}
	}
	printf("Product not found.\n");
}

int main()
{
	loadData();
	printf("***Welcome To Our Stock Site***\n");
	while (1)
	{
		printf("1.Admin Loging\n");
		printf("2.Customer Loging\n");
		printf("Enter Your Choice:");
		int choice;
		scanf("%d", &choice);

		if (choice == 1)
		{
			if (!login_admin())
			{
				printf("\nLogin failed! Exiting...\n");
				return 0;
			}
		}
		else if (choice == 2)
		{
			if (!login_customer())
			{
				printf("\nLogin failed! Exiting...\n");
				return 0;
			}
		}
		else
		{
			printf("Your Input is Invalid !\n");
			break;
		}
	}

	int choice;
	while (1)
	{
		printf("\n========== STOCK & INVENTORY SYSTEM ==========\n");
		printf("1. Add Product\n");
		printf("2. View All Products\n");
		printf("3. Search Product\n");
		printf("4. Update Product\n");
		printf("5. Delete Product\n");
		printf("6. Purchase Stock\n");
		printf("7. Sell Stock\n");
		printf("8. Save & Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			addProduct();
			break;
		case 2:
			viewProducts();
			break;
		case 3:
			searchProduct();
			break;
		case 4:
			updateProduct();
			break;
		case 5:
			deleteProduct();
			break;
		case 6:
			purchaseStock();
			break;
		case 7:
			sellStock();
			break;
		case 8:
			saveData();
			printf("Saved & Exiting...\n");
			exit(0);
		default:
			printf("Invalid choice!\n");
		}
	}
	return 0;
}
