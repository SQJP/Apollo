#Apollo HMI（人机界面）


###先决条件
确保已通过以下方式安装了所需的python包：
```bash
＃所有bash命令都应该从Apollo根目录运行。
sudo pip install modules / tools / py27_requirements.txt
```


###启动服务器
使用默认设置启动服务器：
```bash
bash scripts/ hmi.sh
```

专家可能希望获得更多控制权：
```bash
source scripts/ apollo_base.sh
python modules / hmi / web / hmi_main.py \
     --conf = <your / conf / file> \
     --host = 0.0.0.0 --port = 8899
```

要获得更多帮助信息：
```bash
source scripts/ apollo_base.sh
python modules / hmi / web / hmi_main.py --help | --helpfull
```


###查看HMI
将您的Web浏览器指向http：// localhost：8887（或您的自定义地址）
看主页。
