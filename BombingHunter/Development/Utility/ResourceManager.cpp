#include "ResourceManager.h"
#include"DxLib.h"

//静的メンバ変数定義
ResourceManager* ResourceManager::instance = nullptr;

//リソース管理クラスのインスタンス取得する処理
ResourceManager* ResourceManager::GetInstance()
{
	//インスタンスがなければ、生成する
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	//自分自身のポインタを返却する
	return instance;
}

//リソース管理クラスのインスタンス削除する処理
void ResourceManager::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();
		delete instance;
		instance = nullptr;
	}
}

/*画像取得処理
*  @param file_name ファイルパス
* @param all_num   画像の総数
* @param num_x   横の総数
* @param num_y   縦の総数
* @param size_x    横のサイズ(px)
* @param size_y    縦のサイズ(px)
* @return 読み込んだ画像ハンドルのstd::vector配列
*/
const std::vector<int>& ResourceManager::GetImages(std::string file_name, int all_num,
	int num_x, int num_y, int size_x, int size_y)
{
	//コンテナ内に画像がなければ、画像を読み込む
	if (images_container.count(file_name) == NULL)
	{
		//エラーチェック
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x,
				size_y);
		}
	}

	//コンテナ内の画像データを返却
	return images_container[file_name];
}

const std::vector<int>& ResourceManager::GetSounds(std::string file_name)
{
	//コンテナ内に画像がなければ、画像を読み込む
	if (sounds_container.count(file_name) == NULL)
	{
		CreateSoundsResource(file_name);
	}

	//コンテナ内の画像データを返却
	return sounds_container[file_name];
}

const std::vector<int>& ResourceManager::GetImages(const char* file_name, int all_num,
	int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x,
		size_y);
}

const std::vector<int>& ResourceManager::GetSounds(const char* file_name)
{
	return GetSounds(std::string(file_name));
}

const std::vector<int>& ResourceManager::GetImages(MaterialParam element)
{
	return GetImages(element.file_path, element.all_num, element.num_x,
		element.num_y, element.size_x, element.size_y);
}


/**
* 全ての画像を削除する
* @param material_handle 削除したい画像ハンドルのstd::vector配列
*/
void ResourceManager::UnloadResourcesAll()
{
	//コンテナ内に画像がなければ、処理を終了する
	if (images_container.size() == NULL || sounds_container.size() == NULL)
	{
		return;
	}

	//全ての画像を削除
	for (std::pair<std::string, std::vector<int>> value : images_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}
	for (std::pair<std::string, std::vector<int>> value : sounds_container)
	{
		DeleteSoundMem(value.second[0]);
		value.second.clear();
	}

	//コンテナを開放
	images_container.clear();
}

/**
* 画像ハンドルを読み込みリソースを作成する
* @param file_name ファイルパス
*/
void ResourceManager::CreateImagesResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle = LoadGraph(file_name.c_str());

	//エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	images_container[file_name].push_back(handle);
}

//テスト
void ResourceManager::CreateSoundsResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle = LoadSoundMem(file_name.c_str());

	//エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	sounds_container[file_name].push_back(handle);
}

/**
* 画像ハンドルを読み込みリソースを作成する
* @param file_name ファイルパス
* @param all_num   画像の総数
* @param num_x   横の総数
* @param num_y   縦の総数
* @param size_x    横のサイズ(px)
* @param size_y    縦のサイズ(px)
*/
void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int
	num_y, int size_x, int size_y)
{
	//指定されたファイルを読み込む
	int* handle = new int[all_num];
	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x,
		size_y, handle);

	//エラーチェック
	if (err == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		images_container[file_name].push_back(handle[i]);
	}

	//動的メモリの開放
	delete[] handle;
}
