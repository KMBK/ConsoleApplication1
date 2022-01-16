﻿// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "ImageInfo.h"
#include <filesystem>
#include <fstream>

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
    std::cout << "Process Start.\n";
    std::string indir = std::string(argv[1]);
    int outwidth = atoi(std::string(argv[2]).c_str());
    int outheight = atoi(std::string(argv[3]).c_str());

    auto images = get_images(indir);
    transform_images(images, outwidth, outheight);
    if (std::filesystem::exists("result") == false)
    {
        std::filesystem::create_directory("result");
    }
    save_images(images, "result");
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
