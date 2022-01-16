// プログラム概要
// 引数: [indir] [outdir] [width] [height]
// indirディレクトリから画像ファイル(pngのみ)を読み込み、
// width*heightに拡縮してoutdirディレクトリに出力する。

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "ImageInfo.h"


std::vector<ImageInfo> get_images(std::string indir)
{
    std::vector<ImageInfo> imageinfos;
    for (auto &d : std::filesystem::directory_iterator(indir))
    {
        if (d.path().extension().string() == std::string(".png"))
        {
            ImageInfo info;
            info.Path = d.path().string();
            info.Name = d.path().filename().string();
            info.Image = cv::imread(info.Path);
            imageinfos.push_back(info);
        }
    }
    return imageinfos;
}

void show_images(std::vector<ImageInfo>& images)
{
    for (auto& image : images)
    {
        std::cout << image.Path << std::endl;
    }
}

void transform_images(std::vector<ImageInfo>& images, int width, int height)
{
    for (auto& image : images)
    {
        cv::resize(image.Image, image.Image, cv::Size(width, height));
    }
}

void save_images(std::vector<ImageInfo> images, std::string outdir)
{
    for (auto& image : images)
    {
        auto outpath = std::filesystem::path(outdir) / std::filesystem::path(image.Name);
        cv::imwrite(outpath.string(), image.Image);
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Start." << std::endl;

    //引数をパース
    if (argc != 5)
    {
        std::cout << "引数の数が不正です。" << std::endl;
        return -1;
    }
    std::string indir = std::string(argv[1]);
    if (std::filesystem::exists(indir) == false)
    {
        std::cout << "入力ディレクトリが存在しません。" << std::endl;
        return -1;
    }
    std::string outdir = std::string(argv[2]);

    int outwidth;
    int outheight;
    try 
    {
        outwidth = std::stoi(std::string(argv[3]).c_str());
        outheight = std::stoi(std::string(argv[4]).c_str());
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "出力画像のサイズ指定が不正です。" << std::endl;
        return -1;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "出力画像のサイズ指定が不正です。" << std::endl;
        return -1;
    }
    if (outwidth < 0 || outheight < 0)
    {
        std::cout << "出力画像のサイズ指定が不正です。" << std::endl;
        return -1;
    }

    //画像を取得
    auto images = get_images(indir);
    std::cout << images.size() << "枚の画像を見つけました：" << std::endl;
    
    //取得した画像のフルパス表示
    show_images(images);

    //画像を指定サイズに変換
    std::cout << "画像を" << outwidth << "×" << outheight << "に拡縮します。" << std::endl;
    transform_images(images, outwidth, outheight);
    std::cout << "拡縮処理終了。" <<  std::endl;
    
    std::cout << "画像を" << outdir << "に保存します。" << std::endl;
    //出力ディレクトリに保存
    if (std::filesystem::exists(outdir) == false)
    {
        std::filesystem::create_directory(outdir);
    }
    save_images(images, outdir);
    std::cout << "保存処理終了。" << std::endl;
    
    std::cout << "Finish." << std::endl;
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
