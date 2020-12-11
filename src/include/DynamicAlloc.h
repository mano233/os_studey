//
// Created by mano233 on 2020/12/10.
//

#ifndef DEMO_DYNAMICALLOC_H
#define DEMO_DYNAMICALLOC_H
#include <QObject>
#include <QVariant>
#include <cstdlib>
extern "C" {
extern int mm_init();
extern void mm_free(void* bp);
extern void* mem_malloc(size_t size);
extern void traversal(void (*fun)(void*));
};

class DynamicAlloc : public QObject {
    Q_OBJECT
   private:
    static QVariantList list;
    static QMap<QString, void*> malloc_map;
   public:
    Q_INVOKABLE static void malloc(const QString& id,size_t size);
    Q_INVOKABLE static QVariantList get_list();
};

#endif  // DEMO_DYNAMICALLOC_H
