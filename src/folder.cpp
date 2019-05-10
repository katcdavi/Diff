#include "folder.hpp"

using namespace std;

Folder::Folder(string folderName) : _folderName(folderName), _files() {
    _files = GetFilesInFolder();

    if(_folderName[_folderName.size() - 1] == '/') {
        _folderName = _folderName.substr(0, _folderName.size() - 1);
    }
}

Folder::Folder(const Folder & src) {
    if(&src == this) return;

    _folderName = src._folderName;
}

Folder::~Folder() {
    for(size_t i = 0; i < _files.size(); i++) {
        if(_files[i] != NULL) delete _files[i];
    }
}

vector<File *> Folder::GetFilesInFolder() {
    vector<File *> files;
    
    DIR * d = opendir(_folderName.c_str());
    struct dirent * dp;

    while ((dp = readdir(d)) != NULL) {
        string path = string(dp->d_name);
        if(path == "." || path == "..") continue;

        path = _folderName + "/" + path;        
        if(IO::Exists(path)) {
            File * tmp = CreateFile(path);
            if(tmp != NULL) {
                files.push_back(tmp);
            }
        }
    }

    closedir(d);
    return files;
}

File * Folder::IsInFolder(const string & fileName) const {
    for(size_t i = 0; i < _files.size(); i++) {
        if(_files[i]->GetFileName() == fileName) return _files[i];
    }
    return NULL;
}

void Folder::CompareFolders(const Folder & f) {

}

Result * Folder::CompareWithFile(File * f) {
    File * folderFile = IsInFolder(f->GetFileName());
    Diff * diff = CreateDiff(f, folderFile);

    if(folderFile == NULL || diff == NULL) {
        if(folderFile == NULL) delete folderFile;
        if(diff == NULL) delete diff;
        return new Result(f->GetFileName(), _folderName, false);
    }

    Result * result = diff->Compare();
    delete diff;
    return result;
}

// non-member functions implementation
Folder * CreateFolder(const std::string & filePath) {
    if(!IO::IsDir(filePath)) return NULL;
    return new Folder(filePath);
}