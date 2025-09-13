git rev-list --objects --all | \  
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \  
awk '/blob/ {print substr($0,index($0,$3))}' | \  
sort --numeric-sort --key=2 -r | \  
cut --complement --characters=13-40 | \  
xargs -I {} git show --pretty="" --name-only {}
