#ifndef DEMO_DYNAMICALLOC_H
#define DEMO_DYNAMICALLOC_H
#include <QObject>
#include <QVariant>
#include <QString>
#include <QMap>
#include <cstdlib>
// extern "C" {
//
// };
extern int mm_init();
extern void mm_free(void* bp);
extern void* mem_malloc(size_t size);
extern void traversal(void (*fun)(void*));
extern char* heap_listp;

class DynamicAlloc : public QObject {
    Q_OBJECT
   public:
    Q_INVOKABLE static void malloc(QString id,size_t size);
    Q_INVOKABLE static void free(QString id);
    Q_INVOKABLE static QVariantList get_list();
};

#endif  // DEMO_DYNAMICALLOC_H
