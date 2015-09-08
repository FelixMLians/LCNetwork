//
//  LCBaseRequest.h
//  ShellMoney
//
//  Created by beike on 6/4/15.
//  Copyright (c) 2015 beik. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFURLRequestSerialization.h"
@class AFHTTPRequestOperation;

typedef void (^AFConstructingBlock)(id<AFMultipartFormData> formData);

typedef NS_ENUM(NSInteger , LCRequestMethod) {
    LCRequestMethodGet = 0,
    LCRequestMethodPost,
    LCRequestMethodHead,
    LCRequestMethodPut,
    LCRequestMethodDelete,
    LCRequestMethodPatch
};

/*--------------------------------------------*/
@protocol LCAPIRequest <NSObject>

@required
// 接口参数
@property (nonatomic, strong) NSDictionary *requestArgument;
// 接口地址
- (NSString *)apiMethodName;
// 请求方式
- (LCRequestMethod) requestMethod;

@optional

// 是否是副Url
@property (nonatomic, assign, getter = isViceUrl) BOOL viceUrl;
// 是否缓存数据
- (BOOL) withoutCache;
// 超时时间
- (NSTimeInterval) requestTimeoutInterval;

// 用于上传数据的block
- (AFConstructingBlock)constructingBodyBlock;

// json数据类型验证
- (NSDictionary *)jsonValidator;

// response处理
- (id)responseProcess;
@end

/*--------------------------------------------*/
@class LCBaseRequest;
@protocol LCRequestDelegate <NSObject>

- (void)requestFinished:(LCBaseRequest *)request;
- (void)requestFailed:(LCBaseRequest *)request;

@end
/*--------------------------------------------*/

@protocol LCRequestAccessory <NSObject>

@optional

- (void)requestWillStart:(id)request;
- (void)requestWillStop:(id)request;
- (void)requestDidStop:(id)request;

@end


@interface LCBaseRequest : NSObject

@property (nonatomic, strong) AFHTTPRequestOperation *requestOperation;
@property (nonatomic, weak) id<LCRequestDelegate> delegate;
@property (nonatomic, weak, readonly) id<LCAPIRequest> child;
@property (nonatomic, strong, readonly) id responseJSONObject;
@property (nonatomic, strong, readonly) id cacheJson;
@property (nonatomic, strong, readonly) NSMutableArray *requestAccessories;
@property (nonatomic, copy) void (^successCompletionBlock)(LCBaseRequest *);
@property (nonatomic, copy) void (^failureCompletionBlock)(LCBaseRequest *);


- (void)start;
- (void)stop;


// block回调
- (void)startWithCompletionBlockWithSuccess:(void (^)(id request))success
                                    failure:(void (^)(id request))failure;

- (void)clearCompletionBlock;
- (BOOL)statusCodeValidator;


- (void)addAccessory:(id<LCRequestAccessory>)accessory;

@end


@interface LCBaseRequest (RequestAccessory)

- (void)toggleAccessoriesWillStartCallBack;
- (void)toggleAccessoriesWillStopCallBack;
- (void)toggleAccessoriesDidStopCallBack;


@end

