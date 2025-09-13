#!/bin/bash

move_files_in_sub_dir() {
    parent_folder="$1"
    ele="$2"
    dest_dir="${ele%%.*}"
    echo "Parent folder: $parent_folder"
    echo "dest dir: ${dest_dir}"
    full_path="$parent_folder/$ele"
    dst_path="$parent_folder/$dest_dir"
    echo "Full path: $full_path"
    echo "dst path: $dst_path" 
    rm -fr $dst_path
    if [[ ! -d $dst_path ]]; then
        mkdir -p $dst_path
    fi
    tar -xvzf $full_path -C $dst_path
    for tmq_folder in $(ls $dst_path/log/dm_cache/ ); do
        if [[ $tmq_folder =~ tmq_msg_recorder_(.*) ]]; then
            parent=${BASH_REMATCH[0]}
            child=${BASH_REMATCH[1]}
            mv $dst_path/log/dm_cache/$parent/$child  $dst_path/
        fi
    done
    rm -fr ${dst_path}/log
}

main() {
    for folder in $(ls); do
        for subfolder in $(ls $folder); do 
            p_dir="$folder/$subfolder"
            for ele in $(ls $folder/$subfolder); do 
                if [[ $ele =~ .*.tar.gz ]]; then
                    move_files_in_sub_dir "$p_dir"  "$ele"
                else
                    if [[ -d $folder/$subfolder/$ele ]]; then
                        parent_dir="$folder/$subfolder/$ele"
                        for sub_ele in $(ls $folder/$subfolder/$ele); do
                            if [[ $sub_ele =~ .*.tar.gz ]]; then
                                move_files_in_sub_dir  "$parent_dir" "$sub_ele"
                            fi
                        done
                    fi
                fi
            done
        done
    done 
}

cd ../ultra_datas
main @
